#include <stdio.h>
#include <math.h>

int maxVolume(int S) {
    int a = S / 3;
    int b = (S - a) / 2;
    int c = S - a - b;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 25925925 * 25925926 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:917,execs:371,op:havoc,rep:10)
     * UBSan: signed integer overflow: -178857858 * 25925926 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:917,execs:371,op:havoc,rep:10)
     * UBSan: signed integer overflow: 342916324 * 18519 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:233,execs:103,op:havoc,rep:4)
     */
    return a * b * c;
}

int main(void) {
    int sumSides;
    printf("Enter sum of sides: ");
    if (scanf("%d", &sumSides) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (sumSides < 3) {
        fprintf(stderr, "Sum must be at least 3\n");
        return 1;
    }
    int volume = maxVolume(sumSides);
    printf("Maximum volume: %d\n", volume);
    return 0;
}