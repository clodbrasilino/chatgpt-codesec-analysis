#include <stdio.h>
#include <math.h>
#include <limits.h>

double sumOfGP(int a, int n, int r) {
    double sum = 0;
    if (r == 1) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -1773789777 * 5 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:2294,execs:1956,op:havoc,rep:4)
         */
        if (n > 0 && a * n <= INT_MAX) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -1773789777 * 5 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:2294,execs:1956,op:havoc,rep:4)
             */
            sum = a * n;
        } else {
            sum = a * (double)n;
        }
    } else {
        if (n >= 0) {
            sum = a * (1 - pow(r, n)) / (1 - r);
        }
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