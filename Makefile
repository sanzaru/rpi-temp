CC=cc
LIBS=-lm
OPTS=-Wall --pedantic -O3

all:
	$(CC) $(OPTS) -o rpi-temp rpi-temp.c $(LIBS)

