#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <lib.h>
#include <minix/type.h>
#define MM 0
int setgroup(int pid, char group) {
    message msg;
    msg.m1_i1 = pid;
    msg.m1_i2 = group;
    return _syscall(MM , 80, &msg);
}
int setpri(int pid, int priority) {
    message msg;
    msg.m1_i1 = pid;
    msg.m1_i2 = priority;
    return _syscall(MM ,81 , &msg);
}
int main (int argc, char* argv[])
{
    int a, wynik;
    message m;
    m.m1_i1 = getpid();
   
    setgroup (m.m1_i1, argv[1][0]);
    setpri (m.m1_i1, atoi(argv[2]));
      
    for (a=1; a<1000;a++)  
         wynik = wynik*a;
	
   return 0;
}
