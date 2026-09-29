#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

bool is_non_prime(long long n);

bool is_non_prime(long long n) {
    if (n <= 1) {
        return true;
    }
    if (n == 2) {
        return false;
    }
    if (n % 2 == 0) {
        return true;
    }
    for (long long i = 3; i <= n / i; i += 2) {
        if (n % i == 0) {
            return true;
        }
    }
    return false;
}

int main(void) {
    size_t buf_size = 128;
    char *buffer = (char *)malloc(buf_size);
    long long number;
    char *endptr;

    if (buffer == NULL) {
        return 1;
    }

    if (fgets(buffer, (int)buf_size, stdin) == NULL) {
        free(buffer);
        return 1;
    }

    errno = 0;
    number = strtoll(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer) {
        free(buffer);
        return 1;
    }

    if (is_non_prime(number)) {
        printf("Non-Prime\n");
    } else {
        printf("Prime\n");
    }

    free(buffer);
    return 0;
}