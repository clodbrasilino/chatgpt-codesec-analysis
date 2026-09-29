#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long cube_sum(unsigned int n) {
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        if (sum > ULLONG_MAX - (unsigned long long)i * i * i) {
            return 0;
        }
        sum += (unsigned long long)i * i * i;
    }
    return sum;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    size_t argv_len = 0;
    while (argv[1][argv_len] != '\0') {
        argv_len++;
        if (argv_len >= sizeof(input_buffer)) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < argv_len; i++) {
        input_buffer[i] = argv[1][i];
    }
    input_buffer[argv_len] = '\0';

    char *endptr;
    long val = strtol(input_buffer, &endptr, 10);

    if (endptr == input_buffer || *endptr != '\0' || val < 0 || val > UINT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long result = cube_sum((unsigned int)val);

    if (result == 0 && val > 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}