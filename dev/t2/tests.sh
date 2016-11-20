#!/bin/sh

./set_time 0 2
./set_time 1 5
./set_time 2 10

./bench 2 &
./bench 1 &
./bench 0 &
./bench 2 &
./bench 1 &
./bench 0 

echo 'Changing time'

./set_time 0 20
./set_time 1 40
./set_time 2 100

./bench 2 &
./bench 1 &
./bench 0 &
./bench 2 &
./bench 1 &
./bench 0 
