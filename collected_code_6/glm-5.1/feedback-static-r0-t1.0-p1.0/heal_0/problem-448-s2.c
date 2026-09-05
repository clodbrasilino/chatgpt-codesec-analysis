#include <stdio.h>
#include <stdlib.h>

long long perrin_sum(int n) {
    if (n < 0) {
        return 0;
    }

    long long *buffer = NULL;

    if (n >= 3) {
        buffer = (long long *)malloc(n * sizeof(long long));
        if (buffer == NULL) {
            return 0;
        }

        buffer[0] = 3;
        buffer[1] = 0;
        buffer[2] = 2;

        for (int i = 3; i < n; i++) {
            buffer[i] = buffer[i - 2] + buffer[i - 3];
        }
    }

    long long sum = 0;

    if (n >= 3) {
        for (int i = 0; i < n; i++) {
            sum += buffer[i];
        }
    } else if (n == 2) {
        sum = 3 + 0;
    } else if (n == 1) {
        sum = 3;
    } else {
        sum = 0;
    }

    free(buffer);
    buffer = NULL;

    return sum;
}

int main(void) {
    int n = 10;
    long long result = perrin_sum(n);

    printf("%lld\n", result);

    return 0;
}