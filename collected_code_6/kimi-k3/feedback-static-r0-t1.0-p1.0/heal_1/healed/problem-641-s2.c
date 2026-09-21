#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

uint64_t nonagonal_number(uint64_t n) {
    return n * (7 * n - 5) / 2;
}

int main(void) {
    char buffer[32];
    char *endptr;
    uint64_t n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer) {
        return 1;
    }

    printf("%" PRIu64 "\n", nonagonal_number(n));
    return 0;
}