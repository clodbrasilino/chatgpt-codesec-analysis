#include <stdio.h>
#include <math.h>

double sumOfGP(int a, int n, int r) {
    double sum = 0;
    if (r == 1) {
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