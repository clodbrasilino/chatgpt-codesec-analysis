#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static int hex_is_even(const char *input, bool *is_even)
{
    const unsigned char *p;
    unsigned int last_digit = 0;
    bool found_digit = false;

    if (input == NULL || is_even == NULL) {
        return 0;
    }

    p = (const unsigned char *)input;

    while (isspace(*p)) {
        ++p;
    }

    if (*p == '+') {
        ++p;
    } else if (*p == '-') {
        return 0;
    }

    if (p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
        p += 2;
    }

    while (isxdigit(*p)) {
        if (*p >= '0' && *p <= '9') {
            last_digit = (unsigned int)(*p - '0');
        } else {
            last_digit = (unsigned int)(tolower(*p) - 'a' + 10);
        }

        found_digit = true;
        ++p;
    }

    while (isspace(*p)) {
        ++p;
    }

    if (!found_digit || *p != '\0') {
        return 0;
    }

    *is_even = (last_digit % 2U) == 0U;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    bool is_even;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (memchr(input, '\0', (size_t)length) != NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    if (!hex_is_even(input, &is_even)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (puts(is_even ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}