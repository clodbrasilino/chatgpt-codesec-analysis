#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int extract_quoted_values(const char *input, size_t input_length)
{
    regex_t regex;
    regmatch_t matches[2];
    const char *terminator;
    size_t string_length;
    size_t offset = 0;
    int status;
    int result = -1;

    if (input == NULL || input_length == 0) {
        return -1;
    }

    terminator = memchr(input, '\0', input_length);
    if (terminator == NULL) {
        return -1;
    }

    string_length = (size_t)(terminator - input);

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (offset < string_length) {
        size_t remaining_length = string_length - offset;
        size_t match_end;
        size_t value_start;
        size_t value_end;
        size_t value_length;
        char *value;

        status = regexec(&regex, input + offset, 2, matches, 0);
        if (status == REG_NOMATCH) {
            result = 0;
            goto cleanup;
        }

        if (status != 0 ||
            matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so) {
            goto cleanup;
        }

        match_end = (size_t)matches[0].rm_eo;
        value_start = (size_t)matches[1].rm_so;
        value_end = (size_t)matches[1].rm_eo;

        if (match_end > remaining_length ||
            value_start > value_end ||
            value_end > match_end ||
            value_start > remaining_length ||
            value_end > remaining_length) {
            goto cleanup;
        }

        value_length = value_end - value_start;

        if (value_length > SIZE_MAX - 1) {
            goto cleanup;
        }

        value = malloc(value_length + 1);
        if (value == NULL) {
            goto cleanup;
        }

        if (value_length > 0) {
            memcpy(value, input + offset + value_start, value_length);
        }
        value[value_length] = '\0';

        if (fwrite(value, 1, value_length, stdout) != value_length ||
            fputc('\n', stdout) == EOF) {
            free(value);
            goto cleanup;
        }

        free(value);

        if (match_end == 0 || match_end > remaining_length) {
            goto cleanup;
        }

        offset += match_end;
    }

    result = 0;

cleanup:
    regfree(&regex);
    return result;
}

int main(void)
{
    static const char input[] =
        "name=\"Alice\" city=\"London\" message=\"Hello, world!\"";

    if (extract_quoted_values(input, sizeof(input)) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}