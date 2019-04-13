#!/bin/bash

project=test_timer
if [ -f $project ]
then
    rm -f $project
fi

g++ -g -I../include -o $project $project.cpp -L../build -lx -lpthread
./$project
