#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_decagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return 4ULL * n * n - 3ULL * n;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > 65535 || argv[1][0] == '\0') {
        fprintf(stderr, "Error: Invalid input. n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)val;
    unsigned long long result = find_nth_decagonal_number(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}