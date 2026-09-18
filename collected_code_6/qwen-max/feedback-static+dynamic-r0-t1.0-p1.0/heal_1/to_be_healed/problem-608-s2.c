#include <stdio.h>
#include <stdlib.h>

unsigned long long bellNumber(int n) {
    unsigned long long bell[n+1][n+1];
    bell[0][0] = 1;
    for (int i=1; i<=n; i++) {
        bell[i][0] = bell[i-1][i-1];
        for (int j=1; j<=i; j++)
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
    }
    return bell[n][0];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:357,execs:155,op:havoc,rep:15; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input. Please enter a non-negative integer.\n");
        return EXIT_FAILURE;
    }
    unsigned long long result = bellNumber(n);
    printf("The %dth Bell number is: %llu\n", n, result);
    return EXIT_SUCCESS;
}