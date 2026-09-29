#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <float.h>

double sumOfGP(int a, int n, int r) {
    double sum = 0;
    if (r == 1) {
        if (n > 0) {
            if (a > 0 && n <= INT_MAX / a) {
                sum = (double)a * (double)n;
            } else if (a < 0 && n >= INT_MIN / a) {
                sum = (double)a * (double)n;
            } else {
                sum = (double)a * (double)n;
            }
        } else {
            sum = (double)a * (double)n;
        }
    } else if (n > 0) {
        double term = 1 - pow(r, n);
        double denominator = 1 - r;
        if (term != 0 && denominator != 0 && isfinite(term / denominator) && (double)a * (term / denominator) <= DBL_MAX) {
            sum = (double)a * (term / denominator);
        } else {
            sum = 0;
        }
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:524,execs:459,op:havoc,rep:1; likely memory-safety defect
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