# OpenMP

OpenMP is built into many compilers, including gcc. It has both library
functions and very special compiler directives called **pragmas**. These are
single lines added to C code to tell the compiler that a block of code should be
transformed into code that executes concurrently, or in parallel.

### Simple examples as patterns

All programs we write as experienced software developers have certain kinds of
**patterns** that we follow and adapt over and over again. These patterns are
ways of accomplishing a task that experienced programmers know to be effective.

Professor Shoop has written some small examples of several of these patterns for
parallel programming using openMP. Because they are small and designed to
demononstrate one or two basic concepts, we call them *patternlets*.

# Patternlet Activities

For this activity, you will access instructions on [this
website](http://selkie-macalester.org/csinparallel/modules/Patternlets/build/html/SharedMemory/OpenMP_Patternlets.html).

You should complete patternlets 00-08 and 11.

Scroll down and begin with the first set of OpenMP examples, **Shared Memory
Program Structure and Coordination Patterns**. It will start with an explanation
of the fork-join example that you will try soon. Note that this site has links
labeled Previous and Next. Keep going through each of the 'Next' pages to find
more examples.

## Starter Code

Starter code for all of the patternlets can be found in `openMP/`. 

The first of these examples accessed on the terminal using the following:

    cd openMP/00.forkJoin/

Then build and run:
    
    make
    
    ./forkJoin

The top of the code file has instructions for how to change the code. Build
and run again. After you do that, answer the following question.

* What is the default number of threads given to your code?

# Complete the activities assigned in class

You will work on patternlets in class. 
