#!/bin/bash

if [ -f test ]
then
    rm -f test
fi

g++ -I../include -o test test.cpp -L. -lx
./test
