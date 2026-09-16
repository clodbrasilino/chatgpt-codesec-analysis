#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

int string_starts_with_number(const char *str, long number)
{
    char *endptr;
    long parsed;

    if (str == NULL) {
        return 0;
    }

    if (!isdigit((unsigned char)str[0]) && str[0] != '-' && str[0] != '+') {
        return 0;
    }

    errno = 0;
    parsed = strtol(str, &endptr, 10);

    if (errno == ERANGE) {
        return 0;
    }

    if (endptr == str) {
        return 0;
    }

    return (parsed == number) ? 1 : 0;
}

int main(void)
{
    const char *test1 = "42abc";
    const char *test2 = "100 apples";
    const char *test3 = "hello42";
    const char *test4 = "-7degrees";

    if (string_starts_with_number(test1, 42)) {
        if (printf("\"%s\" starts with 42\n", test1) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 42\n", test1) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (string_starts_with_number(test2, 100)) {
        if (printf("\"%s\" starts with 100\n", test2) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 100\n", test2) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (string_starts_with_number(test3, 42)) {
        if (printf("\"%s\" starts with 42\n", test3) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with 42\n", test3) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (string_starts_with_number(test4, -7)) {
        if (printf("\"%s\" starts with -7\n", test4) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("\"%s\" does not start with -7\n", test4) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}