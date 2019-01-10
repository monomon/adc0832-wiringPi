TARGET = prog
lib_location = ../../
LIBS = -lwiringPi -L $(lib_location) -I $(lib_location) -ladc0832
CC = gcc
CFLAGS = -g -Wall

default: $(TARGET)
all: default

prog: print_adc.o
	$(CC) $(CFLAGS) $< $(LIBS) -o print_adc

print_adc.o: print_adc.c
	$(CC) $(CFLAGS) -c $< $(LIBS) -o print_adc.o

clean:
	-rm -f print_adc.o
	-rm -f print_adc
