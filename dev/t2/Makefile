
all: bench time_ext

bench: bench.c
    cc -o bench bench.c

time_ext: time_ext.c
    cc -o time_ext time_ext.c

run: all
    ./tests.sh
