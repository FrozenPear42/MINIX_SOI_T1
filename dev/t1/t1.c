#include <lib.h>
#include <stdio.h>

int getprocnr(int nr) {
    message msg;
    msg.m1_i1 = nr;
    return _syscall(0, 78, &msg);
}

int main() {
    int nr;
    int i;
    int res;
    printf("PID: ");
    scanf("%d", &nr);
    for(i = nr; i <= nr+10; i++) {
        res = getprocnr(i);
        if(res >= 0)
            printf("PID %d: %d\n", i, res);
        else
            printf("PID %d: ERROR: %d\n", i, errno);
    }
}
