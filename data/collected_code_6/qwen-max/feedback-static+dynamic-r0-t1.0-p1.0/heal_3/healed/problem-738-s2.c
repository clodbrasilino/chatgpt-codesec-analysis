#include <stdio.h>
#include <math.h>

double geometric_sum(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1.0;
    return 1.0 / pow(2, n) + geometric_sum(n - 1);
}

int main() {
    const int test_cases[] = {7, 4, 6};
    for (int i = 0; i < 3; i++) {
        printf("Geometric sum: %f\n", geometric_sum(test_cases[i]));
    }
    return 0;
}