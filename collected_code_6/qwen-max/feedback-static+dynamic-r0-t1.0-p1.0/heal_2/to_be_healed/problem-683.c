#include <stdio.h>
#include <math.h>

int isSumOfTwoSquares(long n) {
    if (n < 0) return 0;
    for (long i = 0; i * i <= n; ++i) {
        long j = sqrt(n - i * i);
        if (i * i + j * j == n && j * j == (n - i * i)) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:159,execs:145,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter a number: ");
    if (scanf("%ld", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (isSumOfTwoSquares(n)) {
        printf("The number can be represented as the sum of two squares.\n");
    } else {
        printf("The number cannot be represented as the sum of two squares.\n");
    }
    return 0;
}