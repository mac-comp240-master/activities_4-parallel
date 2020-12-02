CC=gcc
CPP=g++

all: coinFlip_omp coinFlip_seq

coinFlip_omp: coinFlip_omp_seeds_std_random.cpp
	${CPP} -o coinFlip_omp coinFlip_omp_seeds_std_random.cpp -fopenmp

coinFlip_seq: coinFlip_seq.cpp
	${CPP} -o coinFlip_seq coinFlip_seq.cpp 

clean:
	rm -f coinFlip_omp coinFlip_seq
