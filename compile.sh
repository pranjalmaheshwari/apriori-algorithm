#!/bin/bash

g++ -std=c++11 -O6 -o example apriori.cpp example.cpp -fopenmp -D PARALLEL_MODE=ON

