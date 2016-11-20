#!/bin/sh

time ./tests A 5 &
time ./tests A 10 &
time ./tests B 5 &
time ./tests B 8 &
time ./tests C 5 &
time ./tests C 1 &
