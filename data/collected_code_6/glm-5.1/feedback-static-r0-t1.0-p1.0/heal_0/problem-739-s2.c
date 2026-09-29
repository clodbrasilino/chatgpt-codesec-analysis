#include <stdio.h>
#include <math.h>

int smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    double target = pow(10, n - 1);
    double x = (sqrt(8.0 * target + 1.0) - 1.0) / 2.0;
    long i = (long)ceil(x);
    return (int)i;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int result = smallest_triangular_index(n);
        printf("%d\n", result);
    }
    return 0;
}