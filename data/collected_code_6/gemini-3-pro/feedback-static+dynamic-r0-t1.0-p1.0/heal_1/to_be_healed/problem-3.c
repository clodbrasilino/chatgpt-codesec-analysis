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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    long long number;
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    number = strtoll(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer) {
        return 1;
    }

    if (is_non_prime(number)) {
        printf("Non-Prime\n");
    } else {
        printf("Prime\n");
    }

    return 0;
}