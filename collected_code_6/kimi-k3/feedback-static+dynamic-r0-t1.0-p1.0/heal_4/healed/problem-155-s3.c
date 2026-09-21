#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

uint32_t toggle_even_bits(uint32_t num)
{
    const uint32_t even_bits_mask = 0xAAAAAAAAU;
    return num ^ even_bits_mask;
}

int main(void)
{
    char buffer[32];
    uint32_t number;
    char *endptr;
    unsigned long temp;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    len = strlen(buffer);
    if (len == 0 || (len == sizeof(buffer) - 1 && buffer[len - 1] != '\n')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    temp = strtoul(buffer, &endptr, 10);

    if (endptr == buffer || errno == ERANGE || temp > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    number = (uint32_t)temp;

    printf("%" PRIu32 "\n", toggle_even_bits(number));
    return 0;
}