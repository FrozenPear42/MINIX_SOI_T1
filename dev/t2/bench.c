#include <lib.h>
#include <minix/type.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define MM 0
int setgroup(int pid, char group) {
  message msg;
  msg.m1_i1 = pid;
  msg.m1_i2 = group;
  return _syscall(MM, 80, &msg);
}
int setpri(int pid, int priority) {
  message msg;
  msg.m1_i1 = pid;
  msg.m1_i2 = priority;
  return _syscall(MM, 79, &msg);
}
int main(int argc, char *argv[]) {
  int a, wynik;
  int pri;
  int pid;
  char group;
  pid = getpid();

  group = setgroup(pid, argv[1][0]);
  pri = setpri(pid, atoi(argv[2]));

  printf("[Running  ] PID: %d\tGroup: %c\tPriority: %d\n", pid, group, pri);
  for (a = 1; a < 2000000000; a++)
    wynik = wynik * a;
  printf("[Completed] PID: %d\tGroup: %c\tPriority: %d\n", pid, group, pri);

  return 0;
}
