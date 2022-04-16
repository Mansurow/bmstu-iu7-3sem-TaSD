#!/bin/bash
gcc -std=c99 -Werror -Wall -Wpedantic -Wvla -c *.c
gcc -o main.exe *.o
rm -rf *.o