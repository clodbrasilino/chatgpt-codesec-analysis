#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

uint64_t sum_of_fifth_power_of_odds(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    uint64_t odd = 1;

    for (i = 0; i < n; i++) {
        uint64_t power = odd * odd * odd * odd * odd;
        sum += power;
        odd += 2;
    }

    return sum;
}

int main(void) {
    uint32_t n;
    uint64_t result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long temp;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len == 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n' && !feof(stdin)) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    errno = 0;
    temp = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0' || temp > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint32_t)temp;
    result = sum_of_fifth_power_of_odds(n);
    printf("Sum of fifth power of first %" PRIu32 " odd numbers: %" PRIu64 "\n", n, result);

    return 0;
}