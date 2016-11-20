#!/bin/sh

./bench A 5 &
./bench A 10 &
./bench B 5 &
./bench B 8 &
./bench C 5 &
./bench C 1 

echo "Same groups and priority"

./bench B 10 &
./bench B 10 &
./bench B 10 &
./bench B 10 &
./bench B 10 &
./bench B 10 

echo "Bundle of same groups and priority"

./bench B 10 &
./bench B 10 &
./bench A 10 &
./bench A 10 &
./bench C 10 &
./bench C 10 

