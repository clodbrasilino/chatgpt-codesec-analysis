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

static bool read_int(int *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;
    long parsed;

    if (value == NULL) {
        return false;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return false;
    }

    size_t length = 0U;
    while (length < sizeof buffer && buffer[length] != '\0' &&
           buffer[length] != '\n') {
        ++length;
    }

    if (length == sizeof buffer) {
        return false;
    }

    if (buffer[length] != '\n' && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char discard[128];

        do {
            if (fgets(discard, sizeof discard, stdin) == NULL) {
                break;
            }

            size_t discard_length = 0U;
            while (discard_length < sizeof discard &&
                   discard[discard_length] != '\0' &&
                   discard[discard_length] != '\n') {
                ++discard_length;
            }

            if (discard_length < sizeof discard &&
                discard[discard_length] == '\n') {
                break;
            }
        } while (!feof(stdin));

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

    fputs("Enter an integer: ", stdout);
    fflush(stdout);

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