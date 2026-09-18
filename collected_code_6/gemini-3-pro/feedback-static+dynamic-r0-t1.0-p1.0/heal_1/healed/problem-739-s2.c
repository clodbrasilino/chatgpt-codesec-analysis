#include <stdio.h>
#include <math.h>

long long find_smallest_triangular_index(int n) {
    if (n <= 0 || n >= 39) {
        return -1;
    }
    if (n == 1) {
        return 1;
    }

    double val = pow(10, n - 1);
    double discriminant = 1 + 8 * val;
    long long index = (long long)ceil((-1 + sqrt(discriminant)) / 2.0);

    return index;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    long long index = find_smallest_triangular_index(n);

    if (index == -1) {
        return 1;
    }

    printf("%lld\n", index);

    return 0;
}