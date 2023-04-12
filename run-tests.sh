#!/bin/bash

# script for project 5 example tests

program="project5"
numbers="50 51 52 54 58 59 61 62"
testdir="project5-tests"
diffopts=" -a -i -b -w -B "  # ignore whitespace

g++ -Wall -Werror -std=c++17 -g *.cpp -o $program

for number in $numbers ; do
 
    echo "Running input" $number

    inputfile=$testdir/in$number.txt
    answerfile=$testdir/out$number.txt
    outputfile=actual$number.txt

    ./$program $inputfile > $outputfile

    diff $diffopts $answerfile $outputfile || echo "diff failed on test" $number

    rm $outputfile

done

rm $program

