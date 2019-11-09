# Monte Carlo Computations

Use your ssh client to connect to wulver.macalester.edu.

## Try the examples

There are three C++ code files in this directory, which you will compile
separately on the command line so that you can see how we add a compile flag for
the openmp library and pragmas. Note that though these are C++ code files and
require a different compiler (g++ vs. gcc), you can edit them as if they were C
code.

You should look at the following pages for explanation:

[Top level containing several pages of
explanation](http://selkie-macalester.org/csinparallel/modules/MonteCarloSimulationExemplar/build/html/)

The first couple of pages review how random number generation can be done in C
code for Monte Carlo simulations.

Work on the coin flipping example by going to this [Particular page showing a
sequential version of coin
flipping](http://selkie-macalester.org/csinparallel/modules/MonteCarloSimulationExemplar/build/html/Introduction/CoinFlip.html).

Compile it like this:

    g++ -o coinFlip_seq coinFlip_seq.cpp

Then continue to this [Particular page showing coin flipping in parallel using
one seed for the random
numbers](http://selkie-macalester.org/csinparallel/modules/MonteCarloSimulationExemplar/build/html/Threads/OpenMP_CoinFlip.html)

Compile it like this:

    g++ -o coinFlip_omp coinFlip_omp.cpp -fopenmp

Most importantly, go to and read this [Important page showing how to use
separate seeds for each
thread](http://selkie-macalester.org/csinparallel/modules/MonteCarloSimulationExemplar/build/html/SeedingThreads/SeedEachThread.html)

Compile this finally correctly seeded version like this:

    g++ -o coinFlip_omp_seeds coinFlip_omp_seeds.cpp -fopenmp

This above example is important because this is what you will want to do for
your homework 6 code.

Run the sequential one:

    ./coinFlip_seq
    
Run the properly seeded parallel one, which defaults to 4 threads:

    ./coinFlip_omp_seeds
    
You should see the times for each test case be approximately  4 times as fast
for the parallel version as compared to the sequential version.
