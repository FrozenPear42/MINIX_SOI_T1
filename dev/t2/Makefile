
all: bench time_ext inf set_time

bench: bench.c
	cc -o bench bench.c

time_ext: time_ext.c
	cc -o time_ext time_ext.c

inf: inf.c
	cc -o inf inf.c

set_time: set_time.c
	cc -o set_time set_time.c

run: all
	./tests.sh
