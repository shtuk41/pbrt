CC=c++
CFLAGS=-g -Wall -std=c++11
PBRT_SOURCE=./source/
PBRT_INCLUDE=./source/include

all: 	pbrt

pbrt:	$(PBRT_SOURCE)pbrt.cpp
	$(CC) $(CFLAGS)  -I$(PBRT_SOURCE) -I$(PBRT_INCLUDE) -o pbrt $(PBRT_SOURCE)pbrt.cpp 

clean:
	rm -f pbrt *.o  *.out
