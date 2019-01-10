# adc0832 C library for Raspberry Pi using wiringPi

## Introduction

The ADC0832 is an analog to digital converter with two analog input channels. ([datasheet](http://www.ti.com/lit/ds/symlink/adc0831-n.pdf))

It provides 8-bit resolution for the conversion.

The device can read from the two channels separately, or read a differential voltage between the two channels.

## How to use

The library provides constants for the mux mode, for channel selection, and for the clock interval.

There is a function to set up the pins,
and a function to read data from the adc.

Example:

```
	#define sampling_interval_ms 500
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

```

Note that each read on the adc can use different pins and channels.
The pin numbers, mode and channel are thus passed as arguments to the function,
so that the library can use the flexibility the protocol provides.

## Wiring up the adc

TODO

## Building

Use the provided Makefile to build a static library

   cd adc0832 && make
   
To use it, either copy the library to a common location such as `/usr/lib` or point to it using gcc's `-L` flag.

## Communication protocol

A controller communicates to the adc using 3 pins -
CS (channel select), CLK (clock), and DIO (digital input/output).

This implementation uses a single pin for digital input/output
(switching its direction),
but it is possible to use separate pins. 

The protocol, described in the converter's datasheet, 
consists of a setup phase and a conversion phase.
On each bit communicated, a pulse is sent on the clock pin.

* bring CS pin low to signal beginning of conversion
* start pulsing clock
* output 1 on the digital i/o pin
* output a bit for the mux mode (single-ended or differential)
* output a bit for the channel; the interpretation of this depends on the selected mode.
* this concludes the setup phase; the digital i/o pin is now set to input mode
* on each clock cycle, read a bit from the digital pin; repeat for 8 periods and accumulate the value. The first time data is passed MSB first.
* then the adc passes the same data LSB first. Read in a similar manner to the previous part - pulse 8 clock cycles and read a bit from the device on each.
* the conversion has completed. Set CS pin to high to indicate completion. This will clear the adc's registers.

