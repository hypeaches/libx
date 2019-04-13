#!/bin/bash

project=test_perf_num
if [ -f $project ]
then
    rm -f $project
fi

g++ -g -I../include -o $project $project.cpp -L../build -lx
./$project
