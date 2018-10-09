#!/bin/bash

process="test_object_pool"

if [ -f $process ]
then
    rm -f $process
fi

g++ -g -I../include -o $process $process.cpp -L../build -lx -lpthread
./$process
