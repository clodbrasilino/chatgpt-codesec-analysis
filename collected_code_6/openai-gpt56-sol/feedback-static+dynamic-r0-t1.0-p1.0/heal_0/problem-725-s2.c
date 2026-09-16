#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int extract_quoted_values(const char *input)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *cursor;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    cursor = input;

    while ((status = regexec(&regex, cursor, 2, matches, 0)) == 0) {
        size_t length;
        char *value;

        if (matches[1].rm_so < 0 || matches[1].rm_eo < matches[1].rm_so) {
            regfree(&regex);
            return -1;
        }

        length = (size_t)(matches[1].rm_eo - matches[1].rm_so);

        if (length == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        memcpy(value, cursor + matches[1].rm_so, length);
        value[length] = '\0';

        if (printf("%s\n", value) < 0) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);

        if (matches[0].rm_eo <= 0) {
            regfree(&regex);
            return -1;
        }

        cursor += matches[0].rm_eo;
    }

    regfree(&regex);

    return status == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    const char input[] = "name=\"Alice\" city=\"London\" message=\"Hello, world!\"";

    if (extract_quoted_values(input) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}