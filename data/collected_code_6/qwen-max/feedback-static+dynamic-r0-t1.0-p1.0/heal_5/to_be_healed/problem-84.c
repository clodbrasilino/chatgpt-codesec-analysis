#include <stdio.h>
#include <stdlib.h>

int newman_conway(int n, int *sequence) {
    if (n == 1 || n == 2) {
        sequence[n] = 1;
        return 1;
    }
    if (sequence[n] != 0) {
        return sequence[n];
    }
    int prev1 = newman_conway(n-1, sequence);
    int prev2 = (n - prev1 > 0) ? newman_conway(n - prev1, sequence) : 0;
    sequence[n] = prev1 + prev2;
    return sequence[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:1228,execs:530,op:havoc,rep:11; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }

    int *sequence = (int *)calloc(n + 1, sizeof(int));
    if (sequence == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    sequence[1] = 1;

    if (n > 1) {
        sequence[2] = 1;
    }

    printf("The %d-th number in the Newman-Conway sequence is: %d\n", n, newman_conway(n, sequence));

    free(sequence);
    return 0;
}