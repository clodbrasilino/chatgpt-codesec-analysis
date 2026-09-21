#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

uint64_t rectangular_number(uint32_t n) {
    return (uint64_t)n * ((uint64_t)n + 1);
}

int main(void) {
    char buffer[64];
    char *endptr;
    unsigned long value;
    uint32_t n;

    printf("Enter n: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\n' || value > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint32_t)value;

    printf("%" PRIu64 "\n", rectangular_number(n));

    return 0;
}