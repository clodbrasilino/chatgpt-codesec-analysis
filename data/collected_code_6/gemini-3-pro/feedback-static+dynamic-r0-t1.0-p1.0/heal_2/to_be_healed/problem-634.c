#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t sum_of_fourth_power_even(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; i++) {
        uint64_t even_num = 2ULL * i;
        sum += even_num * even_num * even_num * even_num;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long int parsed_val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || parsed_val < 0) {
        fprintf(stderr, "Invalid input. Please provide a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    uint32_t n = (uint32_t)parsed_val;
    uint64_t result = sum_of_fourth_power_even(n);

    printf("%llu\n", (unsigned long long)result);

    return EXIT_SUCCESS;
}