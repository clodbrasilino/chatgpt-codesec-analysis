#include <stdio.h>
#include <math.h>

int isSumOfTwoSquares(long n) {
    if (n < 0) return 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    long i, j;
    for (i = 0; i * i <= n; ++i) {
        j = sqrt(n - i * i);
        if (i * i + j * j == n) {
            return 1;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:397,execs:168,op:havoc,rep:2; likely memory-safety defect
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