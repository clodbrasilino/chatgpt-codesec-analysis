#include <stdio.h>
#include <stdlib.h>

int count_triangles(int n) {
    if (n <= 0) return 0;
    int count = 0, level = n;
    while (level > 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 66666 * 66667 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:1333,execs:457,op:havoc,rep:1)
         * UBSan: signed integer overflow: 2146137476 + 21572596 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:7064,execs:2376,op:havoc,rep:1)
         * UBSan: signed integer overflow: 2140033685 + 72794555 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:1333,execs:457,op:havoc,rep:1)
         */
        count += (level * (level + 1)) / 2;
        --level;
    }
    return count;
}

int main() {
    int n;
    printf("Enter the number of levels: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    int result = count_triangles(n);
    printf("Number of equilateral triangles: %d\n", result);
    return 0;
}