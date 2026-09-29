#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_SIZE 64

uint64_t nonagonal_number(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    if (n > UINT64_MAX / 7) {
        return 0;
    }
    uint64_t temp = 7 * n;
    if (temp < 5) {
        return 0;
    }
    if ((temp - 5) > UINT64_MAX / n) {
        return 0;
    }
    return n * (temp - 5) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
    char *endptr;
    uint64_t n;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    if (buffer[0] == '\0' || buffer[0] == '\n') {
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        return 1;
    }
    if (len > 0 && buffer[len - 1] != '\n' && !feof(stdin)) {
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer) {
        return 1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return 1;
    }

    if (n > 72340172838076673ULL) {
        return 1;
    }

    printf("%" PRIu64 "\n", nonagonal_number(n));
    return 0;
}