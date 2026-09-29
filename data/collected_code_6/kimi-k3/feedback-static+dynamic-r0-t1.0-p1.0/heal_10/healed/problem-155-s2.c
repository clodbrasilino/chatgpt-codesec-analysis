#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

uint32_t toggle_even_bits(uint32_t num) {
    return num ^ 0xAAAAAAAAu;
}

int main(void) {
    char buffer[64];
    char *endptr;
    uint32_t num;
    unsigned long value;
    size_t len;
    int c;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    if (!memchr(buffer, '\0', sizeof(buffer))) {
        return 1;
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || *endptr != '\0' || value > UINT32_MAX) {
        return 1;
    }

    num = (uint32_t)value;

    printf("%" PRIu32 "\n", toggle_even_bits(num));

    return 0;
}