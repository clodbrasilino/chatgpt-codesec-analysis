#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

double sumOfGP(int a, int n, int r) {
    if (r == 1) {
        long long temp = (long long)a * n;
        /* Possible weaknesses found:
         *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         */
        if (temp > INT_MAX || temp < INT_MIN) {
            return 0;
        }
        return (double)temp;
    } else {
        double numerator = 1 - pow(r, n);
        double denominator = 1 - r;
        if (denominator == 0) {
            return 0;
        }
        return (double)a * (numerator / denominator);
    }
}

int main() {
    int a, n, r;
    printf("Enter the first term, number of terms, and common ratio: ");
    if (scanf("%d %d %d", &a, &n, &r) != 3) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n <= 0 || a == 0) {
        printf("Error in calculation.\n");
        return 1;
    }
    double result = sumOfGP(a, n, r);
    if (result != 0.0) {
        printf("Sum of the geometric progression is: %.2f\n", result);
    } else {
        printf("Error in calculation.\n");
    }
    return 0;
}