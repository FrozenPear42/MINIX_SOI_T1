#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <lib.h>
#include <minix/type.h>
#define MM 0
#define SET_GROUP_TIME 80

int set_group_time(int group, int group_time)
{
    message msg;
    msg.m1_i1 = group;
    msg.m1_i2 = group_time;
    return _syscall(MM, SET_GROUP_TIME, &msg);
}

int main(int argc, char *argv[])
{
    int group;
    int time;

    group = atoi(argv[1]);
    time = atoi(argv[2]);

    set_group_time(group, time);

    return 0;
}