#include <stdio.h>
#include <math.h>

int find_smallest_triangular_index(int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 3;
    }
    double min_val = pow(10, n - 1);
    double c = 2.0 * min_val;
    double k = ceil((-1.0 + sqrt(1.0 + 8.0 * c)) / 2.0);
    return (int)k;
}

int main() {
    int n;
    if (scanf("%d", &n) == 1) {
        int result = find_smallest_triangular_index(n);
        printf("%d\n", result);
        return 0;
    }
    return 1;
}