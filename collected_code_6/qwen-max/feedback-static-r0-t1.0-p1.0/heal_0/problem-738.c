#include <stdio.h>

double geometric_sum(int n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    } else {
        return 1 / pow(2, n) + geometric_sum(n - 1);
    }
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("Geometric sum of %d is: %lf\n", n, geometric_sum(n));
    return 0;
}