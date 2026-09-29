#include <stdio.h>
#include <math.h>
#include <limits.h>

double sumOfGP(int a, int n, int r) {
    if (r == 1) {
        if (n > INT_MAX / a || (a < 0 && n < INT_MIN / a)) {
            return 0;
        }
        return (double)a * n;
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
    double result = sumOfGP(a, n, r);
    if (result != 0.0) {
        printf("Sum of the geometric progression is: %.2f\n", result);
    } else {
        printf("Error in calculation.\n");
    }
    return 0;
}