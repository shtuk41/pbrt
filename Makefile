CC=c++
CFLAGS=-g -Wall -std=c++11
PBRT_SOURCE=./source/
PBRT_INCLUDE=./source/include

all: 	pbrt

pbrt:	$(PBRT_SOURCE)pbrt.cpp transform
	$(CC) $(CFLAGS)  -I$(PBRT_SOURCE) -I$(PBRT_INCLUDE) -o pbrte transform.o $(PBRT_SOURCE)pbrt.cpp 

transform: $(PBRT_SOURCE)transform.cpp
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o transform.o $(PBRT_SOURCE)transform.cpp 

clean:
	rm -f pbrte *.o  *.out
