#!/bin/bash

if [ -f test_perf_num ]
then
    rm -f test_perf_num
fi

g++ -g -I../include -o test_perf_num test_perf_num.cpp -L. -lx
./test_perf_num
