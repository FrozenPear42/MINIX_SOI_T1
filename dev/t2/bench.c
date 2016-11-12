#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <lib.h>
#include <minix/type.h>
#define MM 0
#define ASSIGN_TO_GROUP 79
#define SET_GROUP_TIME 80

int assign_to_group(pid_t pid, int group) {
    message msg;
    msg.m1_i1 = pid;
    msg.m1_i2 = group;
    return _syscall(MM , ASSIGN_TO_GROUP, &msg);
}

int set_group_time(int group, int group_time) {
    message msg;
    msg.m1_i1 = group;
    msg.m1_i2 = group_time;
    return _syscall(MM ,SET_GROUP_TIME, &msg);
}

int main(int argc, char* argv[])
{
    int a, wynik;

    int group = atoi(argv[1]);
    
    assign_to_group (getpid(), group);
      
    for (a=0; a<10000000;a++)
         wynik = wynik*a;
	
   return 0;
}