#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <lib.h>
#include <minix/type.h>
#define MM 0
#define ASSIGN_TO_GROUP 79
#define SET_GROUP_TIME 80

int assign_to_group(int pid, int group) {
    message msg;
    msg.m1_i1 = pid;
    msg.m1_i2 = group;
    return _syscall(MM , ASSIGN_TO_GROUP, &msg);
}

int main(int argc, char* argv[])
{
    int a;
    int pid;
    int res;
    int group;
    
    group = atoi(argv[1]);
    pid = getpid();

    res = assign_to_group (pid, group);

    printf("PID: %d Group: %d\n", pid, res);

    while(1)
         res = res * a;
	
   return 0;
}