#include <errno.h>
#include <limits.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

        regerror(status, NULL, error_message, sizeof(error_message));
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return false;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 1, &match, 0)) == 0) {
        const char *digit = cursor + match.rm_so;
        const char *end = cursor + match.rm_eo;
        unsigned long long value = 0;

        while (digit < end) {
            unsigned int decimal_digit = (unsigned int)(*digit - '0');

            if (value > (ULLONG_MAX - decimal_digit) / 10ULL) {
                fprintf(stderr, "Numeric value is out of range\n");
                regfree(&regex);
                return false;
            }

            value = value * 10ULL + decimal_digit;
            ++digit;
        }

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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