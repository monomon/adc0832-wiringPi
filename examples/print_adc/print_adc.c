/*
 * Read data from the adc and print it out
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <adc0832.h>

#define sampling_interval_ms 500

int main(void)
{
	uchar adc_value;
	
	if (wiringPiSetup() == -1) {
		printf("wiringPi setup failed!\n");
		exit(1);
	}
	
	uint adc_data_pin = 0;
	uint adc_clk_pin = 14;
	uint adc_cs_pin = 15;
	
	adc0832_setup(
		adc_data_pin,
		adc_cs_pin,
		adc_clk_pin
	);
	
	while (1) {
		adc_value = adc0832_read(
			adc_data_pin,
			adc_cs_pin,
			adc_clk_pin,
			adc0832_mode_single_ended,
			adc0832_channel0
		);
			
		printf("adc: %d\n", adc_value);
		delay(sampling_interval_ms);
	}
	
	return 0;
}
