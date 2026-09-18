#include <stdio.h>
#include <math.h>
#include <limits.h>

double sumOfGP(int a, int n, int r) {
    double result = 0;
    if (r == 1) {
        if (n > INT_MAX / a || (a < 0 && n < INT_MIN / a)) {
            return 0;
        }
        result = (double)a * n;
    } else {
        if (r <= -1 || r >= 1) {
            return 0;
        }
        double numerator = 1 - pow(r, n);
        double denominator = 1 - r;
        if (denominator == 0) {
            return 0;
        }
        result = (double)a * (numerator / denominator);
    }
    return result;
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