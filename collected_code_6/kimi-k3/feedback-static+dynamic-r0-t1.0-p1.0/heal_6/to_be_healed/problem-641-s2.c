#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>

uint64_t nonagonal_number(uint64_t n) {
    return n * (7 * n - 5) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf[64];
    uint64_t n;
    char *end;

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    n = strtoull(buf, &end, 10);
    if (errno != 0 || end == buf) {
        return 1;
    }

    printf("%" PRIu64 "\n", nonagonal_number(n));
    return 0;
}