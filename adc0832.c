#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include "adc0832.h"

void adc0832_setup(
	uint data_pin, 
	uint cs_pin,
	uint clk_pin
) {
	pinMode(data_pin, OUTPUT);
	pinMode(cs_pin, OUTPUT);
	pinMode(clk_pin, OUTPUT);
}

uchar adc0832_read(
	uint data_pin, 
	uint cs_pin,
	uint clk_pin,
	uchar mux_mode,
	uchar channel
) {
	// counter
	uchar i;
	// data
	uchar dat1=0, dat2=0;

	pinMode(data_pin, OUTPUT);

	// pulling cs low initiates the decoding
	digitalWrite(cs_pin, LOW);
	digitalWrite(clk_pin, LOW);

	// start bit
	digitalWrite(data_pin, HIGH);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, HIGH);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, LOW);
	
	// set mode
	digitalWrite(data_pin, mux_mode);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, HIGH);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, LOW);
		
	// select channel
	digitalWrite(data_pin, channel);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, HIGH);
	delayMicroseconds(adc0832_period_usec);
	digitalWrite(clk_pin, LOW);
	
	pinMode(data_pin, INPUT);
	
	// msb first data
	for (i=0; i<8; i++)
	{
		digitalWrite(clk_pin, HIGH);
		delayMicroseconds(adc0832_period_usec);
		digitalWrite(clk_pin, LOW);
		delayMicroseconds(adc0832_period_usec);

		dat1 = dat1 << 1 | digitalRead(data_pin);
	}
	
	// lsb first data
	for (i=0; i<8; i++)
	{
		dat2 = dat2 | ((uchar)(digitalRead(data_pin))<<i);
		digitalWrite(clk_pin, HIGH);
		delayMicroseconds(adc0832_period_usec);
		digitalWrite(clk_pin, LOW);
		delayMicroseconds(adc0832_period_usec);
	}
	
	// setting cs high will reset all registers
	// and end the conversion
	digitalWrite(cs_pin, HIGH);
	pinMode(data_pin, OUTPUT);
	
	//~ printf("data is: %x %x\n", dat1, dat2);
	return (dat1 == dat2) ? dat1 : 0;
}
