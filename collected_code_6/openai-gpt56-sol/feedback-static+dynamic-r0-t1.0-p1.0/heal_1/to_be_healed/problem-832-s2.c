#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool extract_maximum(const char *input, unsigned long long *maximum)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    unsigned long long max_value = 0;
    bool found = false;
    int status;

    if (input == NULL || maximum == NULL) {
        return false;
    }

    status = regcomp(&regex, "[0-9]+", REG_EXTENDED);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return false;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t length = (size_t)(match.rm_eo - match.rm_so);
        char *number = malloc(length + 1U);
        unsigned long long value;
        char *end;

        if (number == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return false;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(number, cursor + match.rm_so, length);
        number[length] = '\0';

        errno = 0;
        end = NULL;
        value = strtoull(number, &end, 10);

        if (errno == ERANGE || end == number || *end != '\0') {
            fprintf(stderr, "Numeric value is out of range or invalid: %s\n", number);
            free(number);
            regfree(&regex);
            return false;
        }

        free(number);

        if (!found || value > max_value) {
            max_value = value;
            found = true;
        }

        cursor += match.rm_eo;
    }

    if (status != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex matching failed: %s\n", error_message);
        regfree(&regex);
        return false;
    }

    regfree(&regex);

    if (found) {
        *maximum = max_value;
    }

    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    unsigned long long maximum;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text containing numbers\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!extract_maximum(argv[1], &maximum)) {
        fprintf(stderr, "No valid numeric value found\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", maximum);
    return EXIT_SUCCESS;
}