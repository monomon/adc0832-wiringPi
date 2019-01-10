/*
 * Library for reading from an adc 0832
 * http://www.ti.com/lit/ds/symlink/adc0831-n.pdf
 * 
 * Code largely based on based on
 * https://github.com/jeexzee/roboticarmwateringplants/blob/master/src/servo.c
 */

typedef unsigned char uchar;
typedef unsigned int uint;

#define adc0832_period_usec 2
#define adc0832_mode_differential 0
#define adc0832_mode_single_ended 1
#define adc0832_channel0 0
#define adc0832_channel1 1

// set pin directions
void adc0832_setup(
	uint data_pin, 
	uint cs_pin,
	uint clk_pin
);

// read serial data according to the chip's protocol
uchar adc0832_read(
	uint data_pin, 
	uint cs_pin,
	uint clk_pin,
	uchar mux_mode,
	uchar channel
);
