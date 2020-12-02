/*
 * Demonstation of issues with creating different seeds and with
 * use of rand_r() in stanard C.
 *
 * Shows how C++ has 'classes' in a library called random that makes generating
 * a series of random values, each from a different 'seed' value, easier.
 *
 * Finishes with demonstration 
 */

#include <stdio.h>        // printf()
#include <stdlib.h>       // srand() and rand()
#include <time.h>        // time(), nanosleep()
#include <limits.h>      // to print RAND_MAX, UINT_MAX, INT_MAX
#include <chrono>        // C++ specific library (still doesn' help us really)
#include <random>        // newer C++ library with better ways 
                         // of generating random numbers of variaous types
#include <omp.h>

// Sleep for a certain number of milliseconds
// millisec is length of time to sleep, in milliseconds.
// This is to get different values from the time() function.
void nanoSleep(int millisec) {
    struct timespec req = { millisec/1000, millisec%1000 * 1000000L};
    nanosleep(&req, NULL);
}

// An effort to try to get different values of time for multiple seeds.
// You will see some suggestions online that this provides time in milliseconds.
// Yet even this is not good enough when executed within a loop because the code
// runs very fast.
// Thus, this method also does not provide different results when called 
// multiple times in a loop.
using namespace std::chrono;   // C++ notation
unsigned int getTimeMillis() {
    milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
    // implicit cast to unsigned int is still problematic
    unsigned int timeval = ms.count();  
    printf("debug: timevals: \n");
    printf("%u   ", timeval);
    printf("\n");
    return timeval;
}

//
// It is very popular to use time() to create a large integer as a seed
// for a random number generator function. Let's see what happens when
// we use it in a loop to try to get different seeds.
//
void genSeedsLoop(unsigned int *seeds, int numTimes) {
    int i;
    
    for (i = 0; i<numTimes; i++) {
        seeds[i] = (unsigned) time(NULL); // is there an alternative to time()?
        // nanoSleep(100);   // sleep for 100 milliseconds
        // nanoSleep(1000); // sleep for 1 second
        // seeds[i] = getTimeMillis();
        // seeds[i] = getTimeMillis() + i<<2;  // change each seed-
                                               // this is the best we'll do
    }

    // let's see what we've got for values
    printf("The set of seeds is:\n");
    for (i = 0; i<numTimes; i++) {
        printf("%u  ", seeds[i]);
    }
    printf("\n");

}

// generate a stream of 20 random integer numbers from a seed
// using classic rand_r() function, which has many drawbacks.
//
void genRandomIntStream(unsigned int seed) {
    srand(seed);

    int i;
    int number;
    printf("\n--------------> seed: %u, RAND_MAX is: %d , UINT_MAX is: %u, INT_MAX is: %d\n", seed, RAND_MAX, UINT_MAX, INT_MAX);
    printf("Random integer num stream:\n");
    for (i=0; i<20; i++) {
        number = rand_r(&seed);  // look up info on rand_r. 
                                 // what is max number that can be generated?
        printf("%d  ", number);
    }
    printf("\n");
}

/*
 * Older way of using rand_r to generate 20 random real numbers.
 */
void genRandomRealStream(unsigned int seed) {
    srand(seed);

    int i;
    int number;
    double realValue;
    
    printf("\n--------------> seed: %u\n", seed);
    printf("Random real num stream (between 0.0 and 1.0):\n");
    for (i=0; i<20; i++) {
        number = rand_r(&seed);  // look up info on rand_r. 
                                 // what is max number that can be generated?
        realValue = (double) ((double)number/(double)RAND_MAX);
        printf("%f  ", realValue);
    }
    printf("\n");
}

/*
 * New way of creating array of seeds using C++ std::random_device.
 */
void genSeedsCPPLoop(unsigned int *seeds, int numTimes) {
    int i;
    // use basic random number generation for each seed!!
    std::random_device rd;  
    for (i = 0; i<numTimes; i++) {
        seeds[i] = rd();    // calling rd() gets a new random 32-bit number
    }

    printf("The set of seeds is:\n");
    for (i = 0; i<numTimes; i++) {
        printf("%u  ", seeds[i]);
    }
    printf("\n");
}

// Generate a stream of 20 random real numbers between 0.0 and 1.0
// using newer C++ random number generation libraries.
// Also generate a strem of 20 unsigned integers as a demonstration
// of using the same generator for two different distributions of
// numbers.
void genRandomReal_IntStreamsCPP(unsigned int seedValue){

    double realNumber;
    // simplest generator- less good
    //std::default_random_engine generator;   //declaration of a generator
    // let's use the better 'mt' generator
    // however this one creates at most 2^32 different numbers
    // std::mt19937 generator;   //declaration of a generator
    // even this 64-bit one creates at most 2^32 different numbers
    std::mt19937_64 generator;   //declaration of a generator
    generator.seed(seedValue);

    // declare a distribution of real numbers that we want
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    int i;
    printf("\n--------------> seed: %u\n", seedValue);
    printf("Random real number stream over interval (0.0, 1.0):\n");
    for (i=0; i<20; i++) {
        // use distribution and generator to create a real number
        realNumber = distribution(generator);
        printf("%f   ", realNumber);
    }

    unsigned int uintNumber;
    std::uniform_int_distribution<unsigned int> intDistribution;
    printf("\n--------------> seed: %u\n", seedValue);
    printf("Random unsigned integer number stream :\n");
    for (i=0; i<20; i++) {
        // use distribution and generator to create a real number
        uintNumber = intDistribution(generator);
        printf("%u   ", uintNumber);
    }
}

// Generate a set of seeds, then create a random stream of integer
// values from each of those seeds and a random set of real values
// as doubles between (0.0, 1.0) from each of those seeds.
// The values are simply printed as a demonstration.
void genRandVals(int numTimes) {
    unsigned int seeds[numTimes];
    genSeedsLoop(seeds, numTimes);  // try creating different seeds in a loop

    // TODO: change this to use the same generator for the two distributions

    // try using those seeds to create a series of 'streams' of 
    // random int numbers
    int i;
    for (i = 0; i<numTimes; i++) {
        genRandomIntStream(seeds[i]);
    }
    // We still need to change those numbers to be real numbers, if that is what
    // we actually desire.
    for (i = 0; i<numTimes; i++) {
        genRandomRealStream(seeds[i]);
    }
}

// Use C++ random library to:
// Generate a set of seeds, then create a random stream of real values
// as doubles between (0.0, 1.0) from each of those seeds.
// The values are simply printed as a demonstration.
void genRandValuesCPP(int numTimes) {
    unsigned int seeds[numTimes];

    genSeedsCPPLoop(seeds, numTimes);   // create random set of seeds
    
    // try using those seeds to create a series of 'streams' of random numbers
    int i;
    for (i = 0; i<numTimes; i++) {
        genRandomReal_IntStreamsCPP(seeds[i]);
    }
}

// Demonstrate creation of two random real numbers between (0.0, 1.0) 
// in parallel using the better C++ random class.
//
// Details to notice:
//   - we will let the command line argument that was called numTimes
//     now represent the number of threads to use.
//   - each thread will have one generator as a private variable
//   - more than one private distribution variable can and should be used with
//     the single generator per thread
//
void parallelGenRandValues(int numTimes) {
    
    // now try to create seeds that will then be used by separate threads that
    // will each generate their own 'stream' of random numbers.
    // We'll let numThreads be the same as numTimes for simplicity.

    int numThreads = numTimes;
    unsigned int seeds[numThreads];  // one seed per thread
    genSeedsCPPLoop(seeds, numThreads);
    // seeds now has values in it

    omp_set_num_threads(numThreads);    // set up how many threads we will use

    // warning: 20 is just a hard-coded value for demo purposes
    int numTrials = 20*numThreads; // this essentially means each thread will
                                   // create 20 numbers in the loop below.
    int trialNum;     // loop counter for total trials
    int tid;          // thread id
    int seedValue;         // seed for a particular thread
    std::mt19937_64 generator;   //declaration of a generator for each thread
    
    // declare a distribution of real numbers that we want each thread to use
    double realNumber;  // to hold each new number generated
    std::uniform_real_distribution<double> distribution(0.0,1.0);
    
    unsigned int uintNumber;
    std::uniform_int_distribution<unsigned int> intDistribution;

     // This is an example where some parallel work happens prior 
     // to the for loop.
    #pragma omp parallel default(none) \
        private(trialNum, tid, seedValue, generator, \
        distribution, intDistribution, realNumber, uintNumber) \
        shared(numTrials, seeds) 
    {
        tid = omp_get_thread_num();   // my thread id
        // each thread can get its private copy of a seed (much faster)
        seedValue = seeds[tid];
        // each thread has a private generator
        generator.seed(seedValue);   // use the seed as a start to the generator

        // now have each thread split up the work
        // !!!!!! IMPORTANT : note there is not a second parallel keyword here
        //             we are already forked into threads from previous pragma
        #pragma omp for
        for (trialNum=0; trialNum<numTrials; trialNum++) {
            realNumber = distribution(generator);
            uintNumber = intDistribution(generator);
            printf("tid%d: %f  %u |", tid, realNumber, uintNumber);

        }
        printf("\n");
    }
}

//
// main() to test out issues with random number generation, demo final parallel
// version that provides a reasonable distribution.
//
int main(int argc, char** argv) {

    int numTimes = 4;   // simulating 4 threads sequentially

    if (argc > 1) {
        numTimes = atoi(argv[1]);
    }
    
    // Use older C methods that can be problematic -- sequential --
    printf("=============== Old C random number approach ==================\n");
    // genRandVals(numTimes);

    // Let's try the modern C++ approach (which you should use!) 
    //  -- sequential --
    printf("\n============== Modern C++ approach next =====================\n");
    // genRandValuesCPP(numTimes);
    printf("\n");

    printf("\n============== Parallel C++ approach next ===================\n");
    parallelGenRandValues(numTimes);
    printf("\n");
}