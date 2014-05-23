/**
	This remote protocol allows for higher-level control of several output accessories.
	First byte denotes target device and operation type; further bytes (if any) 
	specify operation arguments.

	Byte 1:
		- first two bits denote the device
		- 00xxxxxx LED matrix 8x8
		- 01xxxxxx LCD keypad (not implemented yet)
		- 1xxxxxxx reserved

	Byte 1 - LED matrix
		- bits 2..4 define the operation
		- __000xxx clear all: no more bytes
		- __001xxV set individual led: needs 1 more byte (4+4 coords)
			- last bit defines the led value
		- __010xxx set a row: needs 1 more byte (row configuration)
			- last 3 bits define row index
		- __011xxx set a column: needs 1 more byte (column configuration)
			- last 3 bits define column index
		- __100xxx set the whole matrix: needs 8 more bytes (rows)
		- __111xxx set brightness: needs 1 more byte (the brightness value)

	EXAMPLES
	========

	Light the 0,0 LED:
	byte 1: 00001001 = 0x9
	byte 2: 00000000 = 0x0

	Light the first LED row:
	byte 1: 00010000 = 0x10
	byte 2: 11111111 = 0xff

	Light the first LED column:
	byte 1: 00011000 = 0x18
	byte 2: 11111111 = 0xff

	Set LED intensity to full
	byte 1: 00111000 = 0x38
	byte 2: 00000111 = 0x7

	Configure all LEDs at once
	byte 1: 00100000 = 0x20
	byte 2..9: 0xff

 */

#define R_DEVICE		B11000000
#define R_DEVICE_LED	B00000000
#define R_DEVICE_LCD	B01000000

#define R_LED_OP		B00111000
#define R_LED_OP_CLEAR	B00000000
#define R_LED_OP_ONE	B00001000
#define R_LED_OP_ROW	B00010000
#define R_LED_OP_COL	B00011000
#define R_LED_OP_ALL	B00100000
#define R_LED_OP_BRIGHT	B00111000
