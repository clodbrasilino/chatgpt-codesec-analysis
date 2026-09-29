#include <stdio.h>
#include <math.h>

int smallestTriangularNumber(int n) {
    double x = (sqrt(8 * pow(10, n - 1) + 1) - 1) / 2;
    return ceil(x);
}

int main() {
    int n;
    printf("Enter the number of digits: ");
    scanf("%d", &n);
    printf("The index of smallest triangular number with %d digits is: %d\n", n, smallestTriangularNumber(n));
    return 0;
}