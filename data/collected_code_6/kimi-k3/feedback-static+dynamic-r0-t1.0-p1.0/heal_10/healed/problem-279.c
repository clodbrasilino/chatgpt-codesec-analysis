#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

uint64_t decagonal_number(uint64_t n) {
    if (n > UINT64_MAX / 4) {
        return 0;
    }
    uint64_t four_n = 4 * n;
    if (four_n < 3) {
        return 0;
    }
    uint64_t factor = four_n - 3;
    if (factor != 0 && n > UINT64_MAX / factor) {
        return 0;
    }
    return n * factor;
}

int main(void) {
    char buffer[128];
    char *endptr;
    uint64_t n;
    size_t len;
    bool valid = true;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 1;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            valid = false;
            break;
        }
    }

    if (!valid) {
        return 1;
    }

    errno = 0;
    n = strtoull(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0') {
        return 1;
    }

    uint64_t result = decagonal_number(n);
    if (result == 0 && n != 0) {
        return 1;
    }

    printf("%" PRIu64 "\n", result);

    return 0;
}