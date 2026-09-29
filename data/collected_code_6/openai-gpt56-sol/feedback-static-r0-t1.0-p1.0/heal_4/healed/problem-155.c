#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    char input[64];
    char *end;
    uintmax_t parsed;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    char *newline = NULL;
    for (char *p = input; *p != '\0'; ++p) {
        if (*p == '\n') {
            newline = p;
            break;
        }
    }

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT32_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu32 "\n",
               toggle_even_bits((uint32_t)parsed)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}