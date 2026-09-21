#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stddef.h>
#include <stdint.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int count = 0;
    int result;

    if (input == NULL) {
        return -1;
    }

    result = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    cursor = input;

    while ((result = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        regoff_t match_start = matches[1].rm_so;
        regoff_t match_end = matches[1].rm_eo;
        regoff_t full_match_end = matches[0].rm_eo;
        size_t length;
        char *value;

        if (match_start < 0 || match_end < match_start || full_match_end <= 0) {
            regfree(&regex);
            return -1;
        }

        if ((uintmax_t)(match_end - match_start) > SIZE_MAX - 1) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match_end - match_start);
        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(value, cursor + (size_t)match_start, length);
        }
        value[length] = '\0';

        if (printf("%s\n", value) < 0) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        cursor += (size_t)full_match_end;
        count++;
    }

    regfree(&regex);

    return result == REG_NOMATCH ? count : -1;
}

int main(int argc, char *argv[])
{
    int count;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    count = extract_quoted_values(argv[1]);
    if (count < 0) {
        if (fprintf(stderr, "Failed to extract quoted values\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}