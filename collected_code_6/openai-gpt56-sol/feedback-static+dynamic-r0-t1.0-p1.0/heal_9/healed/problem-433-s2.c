#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static bool is_greater_than_all(int number, const int array[], size_t length)
{
    if (array == NULL && length != 0U) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (number <= array[i]) {
            return false;
        }
    }

    return true;
}

static bool read_int(int *value)
{
    if (value == NULL) {
        return false;
    }

    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return false;
    }

    char *end = NULL;
    errno = 0;
    long parsed = strtol(line, &end, 10);

    if (end == line || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        free(line);
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    *value = (int)parsed;
    free(line);
    return true;
}

int main(void)
{
    const int array[] = {3, 7, 12, 18, 25};
    const size_t length = sizeof array / sizeof array[0];
    int number;

    if (fputs("Enter an integer: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_int(&number)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    const char *result = is_greater_than_all(number, array, length)
                             ? "is greater than every array element"
                             : "is not greater than every array element";

    if (printf("%d %s.\n", number, result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}