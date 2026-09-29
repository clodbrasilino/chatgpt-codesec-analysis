#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 128U

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
    char input[INPUT_SIZE];

    if (value == NULL) {
        return false;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return false;
    }

    size_t length = 0U;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return false;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        char discard[INPUT_SIZE];
        bool newline_found = false;

        while (fgets(discard, sizeof discard, stdin) != NULL) {
            for (size_t i = 0U; discard[i] != '\0'; ++i) {
                if (discard[i] == '\n') {
                    newline_found = true;
                    break;
                }
            }

            if (newline_found) {
                break;
            }
        }

        return false;
    }

    char *end = NULL;
    errno = 0;
    const long parsed = strtol(input, &end, 10);

    if (end == input || errno == ERANGE ||
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
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (is_greater_than_all(number, array, length)) {
        if (printf("%d is greater than every array element.\n", number) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("%d is not greater than every array element.\n", number) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}