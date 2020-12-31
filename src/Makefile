CC=gcc
CFLAGS=-Wall -pthread
LDLIBS=-lpigpio -lrt
LDFLAGS=-pthread

pinwatcher: pinwatcher.o gpio_perror.o

install: pinwatcher
	cp pinwatcher /usr/local/bin

clean:
	rm -rf *.o pinwatcher
