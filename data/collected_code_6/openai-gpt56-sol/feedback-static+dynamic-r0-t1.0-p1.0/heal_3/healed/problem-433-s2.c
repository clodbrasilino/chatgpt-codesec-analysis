#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

static bool discard_remaining_input(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin);
}

static bool read_int(int *value)
{
    char buffer[128];
    char *end = NULL;
    long parsed;

    if (value == NULL) {
        return false;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    size_t end_index = 0U;
    while (end_index < sizeof buffer && buffer[end_index] != '\0' &&
           buffer[end_index] != '\n') {
        ++end_index;
    }

    if (end_index == sizeof buffer) {
        return false;
    }

    if (buffer[end_index] != '\n' && !feof(stdin)) {
        discard_remaining_input();
        return false;
    }

    errno = 0;
    parsed = strtol(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = (int)parsed;
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
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_greater_than_all(number, array, length)) {
        printf("%d is greater than every array element.\n", number);
    } else {
        printf("%d is not greater than every array element.\n", number);
    }

    return EXIT_SUCCESS;
}