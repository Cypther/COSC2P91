#Long Nguyen #5427059

CC=gcc
CFLAGS=-Wall

all:	shared client

shared:	PoolQueue.so



static:	PoolQueue.o
	mkdir -p lib
	ar rs lib/libPoolQueue.a PoolQueue.o
	mkdir -p include
	cp src/PoolQueue/PoolQueue.h include




client:	client.o PoolQueue.so
	$(CC) -o $@ $(CFLAGS) client.o lib/libPoolQueue.so



client.o:	src/client/client.c src/PoolQueue/PoolQueue.h
	$(CC) $(CFLAGS) -c src/client/client.c -I src/PoolQueue

PoolQueue.o:	src/PoolQueue/PoolQueue.c src/PoolQueue/PoolQueue.h
	$(CC) $(CFLAGS) -c src/PoolQueue/PoolQueue.c


PoolQueue.so:	src/PoolQueue/PoolQueue.c src/PoolQueue/PoolQueue.h
	$(CC) $(CFLAGS) -c -fpic src/PoolQueue/PoolQueue.c
	mkdir -p lib
	$(CC) $(CFLAGS) -shared -o lib/libPoolQueue.so PoolQueue.o
	mkdir -p include
	cp src/PoolQueue/PoolQueue.h include



clean:
	rm -rf lib
	rm -rf include
	rm -f *.o
	rm -f client
