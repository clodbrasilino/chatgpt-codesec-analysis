#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

uint64_t rectangular_number(uint32_t n) {
    return (uint64_t)n * ((uint64_t)n + 1);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long value;
    uint32_t n;
    size_t len;
    int c;

    printf("Enter n: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0' || value > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint32_t)value;

    printf("%" PRIu64 "\n", rectangular_number(n));

    return 0;
}