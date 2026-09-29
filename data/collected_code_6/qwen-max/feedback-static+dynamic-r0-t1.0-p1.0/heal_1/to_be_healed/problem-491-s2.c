#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 341, got <no output>
  *  test case 0 failed: expected 31, got <no output>
  *  test case 2 failed: expected 728, got <no output>
  */

double sumOfGP(int a, int n, int r) {
    double sum = 0;
    if (r == 1) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1111111111 * 5 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:4909,execs:2084,op:havoc,rep:1)
         */
        sum = a * n;
    } else {
        sum = a * (1 - pow(r, n)) / (1 - r);
    }
    return sum;
}

int main() {
    int a, n, r;
    printf("Enter the first term, number of terms, and common ratio: ");
    if (scanf("%d %d %d", &a, &n, &r) != 3) {
        return 1;
    }
    double result = sumOfGP(a, n, r);
    printf("Sum of the geometric progression is: %.2f\n", result);
    return 0;
}