#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_perrin(int n) {
    if (n < 0) {
        return 0;
    }

    if (n == 0) {
        return 3;
    }

    if (n == 1) {
        return 5;
    }

    if (n == 2) {
        return 8;
    }

    unsigned long long *perrin = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (perrin == NULL) {
        return 0;
    }

    perrin[0] = 3;
    perrin[1] = 0;
    perrin[2] = 2;

    unsigned long long sum = 5;

    for (int i = 3; i <= n; i++) {
        perrin[i] = perrin[i - 2] + perrin[i - 3];
        sum += perrin[i];
    }

    free(perrin);

    return sum;
}

int main(void) {
    int n = 10;
    unsigned long long result = sum_perrin(n);

    printf("%llu\n", result);

    return 0;
}