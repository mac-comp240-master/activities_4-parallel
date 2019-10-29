# OpenMP

OpenMP is built into many compilers, including gcc. It has both library
functions and very special compiler directives called **pragmas**. These are
single lines added to C code to tell the compiler that a block of code should be
transformed into code that executes concurrently, or in parallel.

## Simple examples as patterns

All programs we write as experienced software developers have certain kinds of
**patterns** that we follow and adapt over and over again. These patterns are
ways of accomplishing a task that experienced programmers know to be effective.

We have written some small examples of several of these patterns for parallel
programming using openMP. Because they are small and designed to demononstrate
one or two basic concepts, we call them *patternlets*.

## Follow along

I have written some notes about these patternlets, in particular for openMP, on
[this separate site that describes the patterns and the code examples (this is a
link in case it does not show up on your browser very well- click
it!)](http://selkie-macalester.org/csinparallel/modules/Patternlets/build/html/SharedMemory/OpenMP_Patternlets.html).
Follow the descriptions on this page in a separate window of your browser.

If you feel like you need more screen space, the guide that you are reading can
be closed once you understand the instructions below. You may, however, want to
keep it up if you are uncomfortable with the unix command cd for changing
directories, which you will need to use at the terminal many times.

## The Code has instructions in it

There are many examples in separate directories inside the directory called
openMP.

The first of these examples is opened for viewing in the lower left area. You
can place each new one that you try in there by finding it in the directory tree
on the left. For example, the first one can be found by opening openMP, then
opening 00.forkJoin, and finding the .c file inside. This of course is already
done for you for the first one. 

The first of these examples accessed on the terminal by using `cd` to get to the
directory containing it. Each example is in its own directory.

    cd openMP/00.forkJoin/

Then build and run:
    
    make
    
    ./forkJoin

The top of the code file has instructions to try to change the code and build
and run again. After you do that, answer the following question.

{Check It!|assessment}(multiple-choice-930435807)


Each of the examples is in different subdirectories, which you can cd into.
Getting to the next one is done like this:

    cd ../01.forkJoin2/
    
Open the .c code in the lower left panel and look at the directions written as
comments in the file.

# Open the following in your browser

**Please do this, it is very important, because it gives you extra information.**
    
Follow along in a separate browser window on [this separate site that describes
the patterns and the code examples (this is a link in case it does not show up
on your browser very
well)](http://selkie-macalester.org/csinparallel/modules/Patternlets/build/html/SharedMemory/OpenMP_Patternlets.html).

Scroll down and begin with the first set of OpenMP examples, **Shared Memory
Program Structure and Coordination Patterns**, by clicking on the link. It will
start with an explanation of the fork-join example that you just tried. Note
that this site has links labeled Previous and Next. Keep going through each of
the 'Next' pages to find more examples.
