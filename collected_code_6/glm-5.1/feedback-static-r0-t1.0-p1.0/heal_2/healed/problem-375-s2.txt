#include <stdio.h>
#include <stdlib.h>

long long round_to_nearest_multiple(long long number, long long multiple) {
    if (multiple == 0) {
        return 0;
    }

    long long half = multiple / 2;
    long long remainder = number % multiple;

    if (remainder < 0) {
        remainder += multiple;
        half += multiple % 2;
    }

    if (remainder >= half) {
        return number - remainder + multiple;
    }

    return number - remainder;
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *endptr1;
    char *endptr2;
    long long number = strtoll(argv[1], &endptr1, 10);
    long long multiple = strtoll(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || multiple == 0) {
        return EXIT_FAILURE;
    }

    long long result = round_to_nearest_multiple(number, multiple);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}