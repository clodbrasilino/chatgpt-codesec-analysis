#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

uint64_t rectangular_number(uint32_t n) {
    return (uint64_t)n * ((uint64_t)n + 1);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    uint32_t n;
    uintmax_t temp;
    char *endptr;

    printf("Enter n: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    temp = strtoumax(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || temp > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint32_t)temp;

    printf("%" PRIu64 "\n", rectangular_number(n));

    return 0;
}