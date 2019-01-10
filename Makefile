TARGET = lib
LIBS = -lwiringPi
CC = gcc
CFLAGS = -g -Wall

default: $(TARGET)

adc0832.o: adc0832.c
	$(CC) $(CFLAGS) -c adc0832.c $(LIBS) -o adc0832.o

lib: adc0832.o
	ar rcs libadc0832.a adc0832.o

clean:
	-rm -f *.o
	-rm -f *.a
