#include <stdio.h>

#include "qrean.h"
#include "image.h"
#include "detector.h"
#include "debug.h"

char imagebuf[3 * 1024 * 1024];
char inputbuf[1024];
char outputbuf[1024];

image_t* make(int type, int datatype, int qr_errorlevel, int qr_version, int qr_maskpattern, int padding, int scale) {
	qrean_t qrean = create_qrean(type);

	qrean_set_qr_version(&qrean, qr_version);
	qrean_set_qr_maskpattern(&qrean, qr_maskpattern);
	qrean_set_qr_errorlevel(&qrean, qr_errorlevel);
	qrean_set_bitmap_padding(&qrean, create_padding1(padding));
	qrean_set_bitmap_scale(&qrean, scale);

	int res = qrean_write_string(&qrean, inputbuf, datatype);
	if (!res) {
		return 0;
	}

	size_t width = qrean_get_bitmap_width(&qrean);
	size_t height = qrean_get_bitmap_height(&qrean);

	image_t* img = (image_t*)imagebuf;
	img->buffer = (image_pixel_t*)(((char*)img) + sizeof(image_t));
	img->width = width;
	img->height = height;

	qrean_set_bitmap_color(&qrean, 0x000000FF, 0xFFFFFFFF);
	qrean_read_bitmap(&qrean, img->buffer, width * height * 4, 32);

	return img;
}

__attribute__((import_module("env"), import_name("on_found")))
extern void on_found_js(int type, const char *str);

static void on_found(qrean_detector_perspective_t *warp, void *opaque) {
	qrean_read_string(warp->qrean, outputbuf, sizeof(outputbuf));
	on_found_js(warp->qrean->code->type, outputbuf);
}

int detect() {
	double gamma_value = 1.8;

	outputbuf[0] = '\0';
	image_t* img = (image_t*)imagebuf;

	// overwrite. it's safe with src == dst
	image_digitize(img, img, gamma_value);

	int num_candidates = 0;
	qrean_detector_qr_finder_candidate_t* candidates = qrean_detector_scan_qr_finder_pattern(img, &num_candidates);
	int found = 0;

	found += qrean_detector_try_decode_qr(img, candidates, num_candidates, on_found, NULL);
	found += qrean_detector_try_decode_mqr(img, candidates, num_candidates, on_found, NULL);
	found += qrean_detector_try_decode_rmqr(img, candidates, num_candidates, on_found, NULL);
	found += qrean_detector_try_decode_tqr(img, candidates, num_candidates, on_found, NULL);
	found += qrean_detector_scan_barcodes(img, on_found, NULL);

	return found;
}
