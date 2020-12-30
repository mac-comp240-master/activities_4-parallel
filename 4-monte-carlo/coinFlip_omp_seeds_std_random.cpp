/*
  Original code provided by Dave Valentine, Slippery Rock University.
  Edited by Libby Shoop, Macalester College.
*/
//
//  NOTE: this version is a variant of coinFlip_omp.cpp,
//        where we create a different seed for each thread.
//        

//
// Simulate many coin flips with rand_r() on multiple threads
// to determine how random the values are that are returned
// from each call.
//

#include <stdio.h>        // printf()
#include <stdlib.h>       // srand() and rand()
#include <time.h>        // time()
#include <random>        // newer C++ library with better ways 
                         // of generating random numbers of variaous types

#include <omp.h>         // OpenMP functions and pragmas

/***  OMP ***/
const int nThreads = 4;  // number of threads to use
unsigned int seeds[nThreads];

void seedThreads() {
    int my_thread_id;
    unsigned int seed;
    #pragma omp parallel private (seed, my_thread_id)
    {
        my_thread_id = omp_get_thread_num();
        
        //create seed on thread using current time
        unsigned int seed = (unsigned) time(NULL);
        
        //munge the seed using our thread number so that each thread has its
        //own unique seed, therefore ensuring it will generate a different set of numbers
        seeds[my_thread_id] = (seed & 0xFFFFFFF0) | (my_thread_id + 1);
        
        printf("Thread %d has seed %u\n", my_thread_id, seeds[my_thread_id]);
    }
    
}
/***  OMP ***/

//Standard chi sqaure test
double chiSq(int heads, int tails) {
	double sum = 0;					//chi square sum
	double tot = heads+tails;		//total flips
	double expected = 0.5 * tot;	//expected heads (or tails)
	
	sum = ((heads - expected)*(heads-expected)/expected) + \
		((tails - expected)*(tails-expected)/expected);
	return sum;
}

void genSeeds(unsigned int *seeds, int numTimes) {
    int i;
    // use basic random number generation for each seed!!
    std::random_device rd;  
    for (i = 0; i<numTimes; i++) {
        seeds[i] = rd();    // calling rd() gets a new random 32-bit number
    }
}


int main(int argc, char *argv[]) {
	int numFlips,			//loop control
		numHeads, numTails;	//counters
    
    /***  OMP ***/
    double ompStartTime, ompStopTime;   
    int tid;       // thread id when forking threads in for loop
    /***  OMP ***/
    
    unsigned int seed;   // seed each thread will use in for loop

/***** Initialization *****/
    unsigned int seeds[nThreads] ; // one seed per thread
    genSeeds(seeds, nThreads);

    /***  OMP ***/ 
    omp_set_num_threads(nThreads);  
    // seedThreads();
    /***  OMP ***/ 

    int trialFlips = 256;
    if (argc >1) {
        trialFlips = atoi(argv[1]);  // 
    }
    
	printf("Threaded Simulation of %d Coin Flips using C++ random library and %d threads.\n", trialFlips, nThreads);
	
	//print our heading text
	printf("\n\n%15s%15s%15s%15s%15s%15s",
           "Trials","numHeads","numTails","total",
           "Chi Squared", "Time (sec)\n");
    
    

// Try several trials of different numbers of flips doubling how many each round.
// 
// Use a unsigned int because we will try a great deal of flips for some trials.
    // unsigned int trialFlips = 256;          // start with a smal number of flips
    unsigned int maxFlips = 1073741824;     // this will be a total of 23 trials
    // while (trialFlips <= maxFlips) {  // below we will double the number of 
                                      // trial flips and come back here
                                      // and run another trial,
                                      // until we have reached > maxFlips.
        
        numHeads = 0;               //reset counters
        numTails = 0;
        
        /***  OMP ***/
        ompStartTime = omp_get_wtime();   //get start time for this trial
    
    /***** Flip a coin trialFlips times, on each thread in parallel,
     *     with each thread getting its 1/4 share of the total flips.
     *****/
    /*
    
/***  OMP ***/    
#pragma omp parallel num_threads(nThreads) default(none) \
        private(numFlips, tid, seed) \
        shared(trialFlips, seeds) \
        reduction(+:numHeads, numTails)
    {
        tid = omp_get_thread_num();   // my thread id
        // seed = seeds[tid];            // it is much faster to keep a 
                                      // private copy of our seed
		
        std::random_device rd;

        // since declared here, these are automatically private
        // std::mt19937_64 generator;  //declaration of a generator for each thread
        unsigned int uintNumber;    // random nuber from distribution
        // std::uniform_int_distribution<unsigned int> intDistribution;

        // each thread has a private generator
        
        // generator.seed(seed);   // use the seed as a start to the generator
        
        unsigned int one = 1U;
        #pragma omp for
        for (numFlips=0; numFlips<trialFlips; numFlips++) {
            // uintNumber = intDistribution(generator);
            uintNumber = rd();
            // could do this, but ... be faster
            // if (uintNumber%2 == 0) // if random number is even, call it heads
            //     numHeads++;       
            // else
            //     numTails++;
            if (uintNumber & one) // if random number is odd, call it tails
                numTails++;       
            else
                numHeads++;
        }
        
    }
        /***  OMP ***/
        ompStopTime = omp_get_wtime();
        
        // Finish this trial by printing out results

        printf("%15d%15d%15d%15d%15.6f%15.6f\n", trialFlips, numHeads, numTails,
               (numHeads+numTails), chiSq(numHeads, numTails),
               (double)(ompStopTime-ompStartTime));    /***  OMP ***/

        // trialFlips *= 2;   // double the number of flips for the next trial

        
    // }

/***** Finish Up *****/
	// printf("\n\n\t<<< Normal Termination >>>\n\n");
	return 0;
}

