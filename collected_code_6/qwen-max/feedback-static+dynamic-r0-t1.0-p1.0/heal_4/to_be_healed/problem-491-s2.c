#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

double sumOfGP(int a, int n, int r) {
    double sum = 0;
    if (r == 1) {
        if (n > 0) {
            if (a > 0 && n <= INT_MAX / a) {
                sum = a * n;
            } else if (a < 0 && n <= INT_MIN / a) {
                sum = a * n;
            } else {
                sum = a * (double)n;
            }
        } else {
            sum = a * (double)n;
        }
    } else if (n >= 0) {
        if (a * (1 - pow(r, n)) / (1 - r) <= DBL_MAX) {
            sum = a * (1 - pow(r, n)) / (1 - r);
        } else {
            sum = 0; 
        }
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000006,time:1330,execs:1393,op:havoc,rep:1; likely memory-safety defect
  */

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