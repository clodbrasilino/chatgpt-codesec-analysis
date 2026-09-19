#include <errno.h>
#include <inttypes.h>
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
        char error_message[256];

        regerror(status, &regex, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return false;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        size_t length;
        char *number;
        char *end;
        unsigned long long value;

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return false;
        }

        length = (size_t)(match.rm_eo - match.rm_so);

        if (length == SIZE_MAX) {
            fprintf(stderr, "Numeric value is too long\n");
            regfree(&regex);
            return false;
        }

        number = malloc(length + 1U);
        if (number == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return false;
        }

        memcpy(number, cursor + match.rm_so, length);
        number[length] = '\0';

        errno = 0;
        value = strtoull(number, &end, 10);

        if (errno == ERANGE || end == number || *end != '\0') {
            fprintf(stderr,
                    "Numeric value is out of range or invalid: %s\n",
                    number);
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

int main(int argc, const char *const argv[])
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