#ifndef __QR_QRSPEC_H__
#define __QR_QRSPEC_H__

#include <stdint.h>
#include <stdio.h>

typedef enum {
	QR_VERSION_INVALID = -1,
	QR_VERSION_AUTO = 0,

	QR_VERSION_1,
	QR_VERSION_2,
	QR_VERSION_3,
	QR_VERSION_4,
	QR_VERSION_5,
	QR_VERSION_6,
	QR_VERSION_7,
	QR_VERSION_8,
	QR_VERSION_9,
	QR_VERSION_10,
	QR_VERSION_11,
	QR_VERSION_12,
	QR_VERSION_13,
	QR_VERSION_14,
	QR_VERSION_15,
	QR_VERSION_16,
	QR_VERSION_17,
	QR_VERSION_18,
	QR_VERSION_19,
	QR_VERSION_20,
	QR_VERSION_21,
	QR_VERSION_22,
	QR_VERSION_23,
	QR_VERSION_24,
	QR_VERSION_25,
	QR_VERSION_26,
	QR_VERSION_27,
	QR_VERSION_28,
	QR_VERSION_29,
	QR_VERSION_30,
	QR_VERSION_31,
	QR_VERSION_32,
	QR_VERSION_33,
	QR_VERSION_34,
	QR_VERSION_35,
	QR_VERSION_36,
	QR_VERSION_37,
	QR_VERSION_38,
	QR_VERSION_39,
	QR_VERSION_40,

	// mQR
	QR_VERSION_M1,
	QR_VERSION_M2,
	QR_VERSION_M3,
	QR_VERSION_M4,

	// rMQR
	QR_VERSION_R7x43, //  0
	QR_VERSION_R7x59, //  1
	QR_VERSION_R7x77, //  2
	QR_VERSION_R7x99, //  3
	QR_VERSION_R7x139, //  4

	QR_VERSION_R9x43, //  5
	QR_VERSION_R9x59, //  6
	QR_VERSION_R9x77, //  7
	QR_VERSION_R9x99, //  8
	QR_VERSION_R9x139, //  9

	QR_VERSION_R11x27, // 10 (!)
	QR_VERSION_R11x43, // 11
	QR_VERSION_R11x59, // 12
	QR_VERSION_R11x77, // 13
	QR_VERSION_R11x99, // 14
	QR_VERSION_R11x139, // 15

	QR_VERSION_R13x27, // 16 (!)
	QR_VERSION_R13x43, // 17
	QR_VERSION_R13x59, // 18
	QR_VERSION_R13x77, // 19
	QR_VERSION_R13x99, // 20
	QR_VERSION_R13x139, // 21

	QR_VERSION_R15x43, // 22
	QR_VERSION_R15x59, // 23
	QR_VERSION_R15x77, // 24
	QR_VERSION_R15x99, // 25
	QR_VERSION_R15x139, // 26

	QR_VERSION_R17x43, // 27
	QR_VERSION_R17x59, // 28
	QR_VERSION_R17x77, // 29
	QR_VERSION_R17x99, // 30
	QR_VERSION_R17x139, // 31

	QR_VERSION_TQR,
} qr_version_t;

typedef enum {
	QR_ERRORLEVEL_INVALID = -1,

	QR_ERRORLEVEL_L,
	QR_ERRORLEVEL_M,
	QR_ERRORLEVEL_Q,
	QR_ERRORLEVEL_H,
} qr_errorlevel_t;

typedef enum {
	QR_MASKPATTERN_INVALID = -1,

	QR_MASKPATTERN_0,
	QR_MASKPATTERN_1,
	QR_MASKPATTERN_2,
	QR_MASKPATTERN_3,
	QR_MASKPATTERN_4,
	QR_MASKPATTERN_5,
	QR_MASKPATTERN_6,
	QR_MASKPATTERN_7,

	QR_MASKPATTERN_NONE,
	QR_MASKPATTERN_ALL,

	QR_MASKPATTERN_AUTO,
} qr_maskpattern_t;

#define IS_MQR(version)  (QR_VERSION_M1 <= (version) && (version) <= QR_VERSION_M4)
#define IS_QR(version)   (QR_VERSION_1 <= (version) && (version) <= QR_VERSION_40)
#define IS_RMQR(version) (QR_VERSION_R7x43 <= (version) && (version) <= QR_VERSION_R17x139)
#define IS_TQR(version)  ((version) == QR_VERSION_TQR)

uint_fast8_t qrspec_get_symbol_width(qr_version_t version);
uint_fast8_t qrspec_get_symbol_height(qr_version_t version);

uint_fast8_t qrspec_get_alignment_num(qr_version_t version);
uint_fast8_t qrspec_get_alignment_steps(qr_version_t version, uint_fast8_t step);
uint_fast8_t qrspec_get_alignment_position_x(qr_version_t version, uint_fast8_t idx);
uint_fast8_t qrspec_get_alignment_position_y(qr_version_t version, uint_fast8_t idx);

size_t qrspec_get_available_bits(qr_version_t version);
uint_fast8_t qrspec_get_total_blocks(qr_version_t version, qr_errorlevel_t level);
uint_fast8_t qrspec_get_error_words_in_block(qr_version_t version, qr_errorlevel_t level);

uint_fast8_t qrspec_get_data_bitlength_for(qr_version_t version, int mode);

const char *qrspec_get_version_string(qr_version_t version);
qr_version_t qrspec_get_version_by_string(const char *version);

int qrspec_is_valid_combination(qr_version_t version, qr_errorlevel_t level, qr_maskpattern_t mask);

#endif /* __QR_QRSPEC_H__ */
