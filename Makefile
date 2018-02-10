CC=c++
CFLAGS=-g -Wall -std=c++11
PBRT_SOURCE=./source/
PBRT_INCLUDE=./source/include

all: 	pbrt

pbrt:	geometry  $(PBRT_SOURCE)pbrt.cpp ray
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -o pbrt geometry.o $(PBRT_SOURCE)pbrt.cpp ray.o

geometry:	$(PBRT_SOURCE)geometry.cpp
	$(CC) $(CFLAGS) $(PBRT_SOURCE)geometry.cpp -c -o geometry.o -I$(PBRT_INCLUDE)
	
ray:	$(PBRT_SOURCE)ray.cpp
	$(CC) $(CFLAGS) $(PBRT_SOURCE)ray.cpp -c -o ray.o -I$(PBRT_INCLUDE)

clean:
	rm -f pbrt *.o  *.out
