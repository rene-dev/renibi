CC = g++
CFLAGS = -O3 -g -Wall

renibi:	filter.o open.o hsv.o renibi.o save.o alles.h
	$(CC) $(CFLAGS) filter.o hsv.o  open.o  renibi.o  save.o -o renibi
	
save.o:	alles.h save.cpp
	$(CC) $(CFLAGS) -c save.cpp

open.o:	alles.h open.cpp
	$(CC) $(CFLAGS) -c open.cpp

hsv.o:	alles.h hsv.cpp
	$(CC) $(CFLAGS) -c hsv.cpp

filter.o:	alles.h filter.cpp
	$(CC) $(CFLAGS) -c filter.cpp

renibi.o:	alles.h renibi.cpp
	$(CC) $(CFLAGS) -c renibi.cpp

clean:
	rm -f *.o
	rm -f renibi
	rm -f getlog
	rm -f *~
	rm -f *.ppm

all:
	make clean
	make