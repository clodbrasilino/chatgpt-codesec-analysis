#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int isWoodall(unsigned long long number) {
    unsigned int n;
    unsigned int bits = (unsigned int)(sizeof(number) * CHAR_BIT);

    for (n = 1; n < bits; ++n) {
        unsigned long long power = 1ULL << n;

        if (power > ULLONG_MAX / n) {
            break;
        }

        unsigned long long woodall = n * power - 1;

        if (woodall == number) {
            return 1;
        }

        if (woodall > number) {
            break;
        }
    }

    return 0;
}

int main(void) {
    char buffer[64];
    char *endptr;
    unsigned long long number;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    number = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }

    printf("%s\n", isWoodall(number) ? "Yes" : "No");

    return 0;
}