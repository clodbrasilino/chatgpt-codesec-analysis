#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

int64_t nth_carol_number(unsigned int n);

int64_t nth_carol_number(unsigned int n) {
    if (n == 0 || n > 31) {
        return 0;
    }
    int64_t power_of_two = 1LL << n;
    int64_t term = power_of_two - 1;
    return (term * term) - 2;
}

int main(int argc, const char *const argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    long input = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || input < 1 || input > 31) {
        printf("Error: input must be an integer between 1 and 31.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)input;
    int64_t result = nth_carol_number(n);
    
    printf("%lld\n", (long long)result);

    return EXIT_SUCCESS;
}