#!/bin/sh

./time_ext 0 ./bench 0 &
./time_ext 1 ./bench 1 &
./time_ext 2 ./bench 2 &
./time_ext 0 ./bench 0 &
./time_ext 1 ./bench 1 &
./time_ext 2 ./bench 2 &
