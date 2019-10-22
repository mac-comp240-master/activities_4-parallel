#!/bin/bash

# this runs either the sequential or parallel omp version of the monte carlo
# pi program 'n' times for a given problem size and number of threads.

# Author: Libby Shoop

problem_size=$1   #first argument is problem size
num_threads=$2    #second argument is number of threads
num_times=$3      #third argument is number of times to run the test

if [  "$num_threads" == "1"  ]; then
  command="./trap-seq $problem_size"
else
  command="./trap-omp $problem_size $num_threads"
fi

echo "==============  Running " $num_times "tests of : " $command

#for test in {1..$numtimes}
#do
counter=1
while [ $counter -le $num_times ]
do
  echo "++++++++++++++++++++++ test" $counter "+++++++++++++++++++++++++++"
  $command
  ((counter++))
done
