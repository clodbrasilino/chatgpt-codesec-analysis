#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int extract_quoted_values(const char *input)
{
    static const char pattern[] = "\"([^\"]*)\"";
    const char *current;
    regex_t regex;
    regmatch_t matches[2];
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    current = input;

    while ((status = regexec(&regex, current, 2, matches, 0)) == 0) {
        size_t start;
        size_t end;
        size_t length;
        char *value;

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so) {
            regfree(&regex);
            return -1;
        }

        start = (size_t)matches[1].rm_so;
        end = (size_t)matches[1].rm_eo;

        if (end < start) {
            regfree(&regex);
            return -1;
        }

        length = end - start;

        if (length > SIZE_MAX - 1) {
            regfree(&regex);
            return -1;
        }

        value = malloc(length + 1);
        if (value == NULL) {
            regfree(&regex);
            return -1;
        }

        if (length > 0) {
            memcpy(value, current + start, length);
        }
        value[length] = '\0';

        if (fwrite(value, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            regfree(&regex);
            return -1;
        }

        free(value);
        current += (size_t)matches[0].rm_eo;
    }

    regfree(&regex);
    return status == REG_NOMATCH ? 0 : -1;
}

int main(void)
{
    const char *input =
        "The values are \"first\", \"second value\", and \"third\".";

    if (extract_quoted_values(input) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}