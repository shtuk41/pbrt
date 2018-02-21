CC=c++
CFLAGS=-g -Wall -std=c++11
PBRT_SOURCE=./source/
PBRT_INCLUDE=./source/include

all: 	pbrt

pbrt:	$(PBRT_SOURCE)pbrt.cpp transform ray quaternion animatedtransform interval interaction
	$(CC) $(CFLAGS)  -I$(PBRT_SOURCE) -I$(PBRT_INCLUDE) -o pbrte transform.o ray.o quaternion.o animatedtransform.o interval.o $(PBRT_SOURCE)pbrt.cpp 

transform: $(PBRT_SOURCE)transform.cpp 
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o transform.o $(PBRT_SOURCE)transform.cpp 

ray:
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o ray.o $(PBRT_SOURCE)ray.cpp 

quaternion:
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o quaternion.o $(PBRT_SOURCE)quaternion.cpp 

animatedtransform:
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o animatedtransform.o $(PBRT_SOURCE)animatedtransform.cpp 

interval:
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o interval.o $(PBRT_SOURCE)interval.cpp 

interaction:
	$(CC) $(CFLAGS)  -I$(PBRT_INCLUDE) -I$(PBRT_SOURCE) -c -o interaction.o $(PBRT_SOURCE)interaction.cpp 


clean:
	rm -f pbrte *.o  *.out
