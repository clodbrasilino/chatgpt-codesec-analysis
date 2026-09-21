#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int extract_quoted_values(const char *input, size_t input_length)
{
    static const char pattern[] = "\"([^\"]*)\"";
    regex_t regex;
    regmatch_t matches[2];
    char *buffer = NULL;
    size_t offset = 0;
    int status;
    int result = -1;

    if (input == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        return -1;
    }

    if (input_length > 0) {
        memcpy(buffer, input, input_length);
    }
    buffer[input_length] = '\0';

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(buffer);
        return -1;
    }

    while (offset < input_length) {
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;
        size_t consumed;
        size_t value_length;

        status = regexec(&regex, buffer + offset, 2, matches, 0);

        if (status == REG_NOMATCH) {
            result = 0;
            break;
        }

        if (status != 0 ||
            matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so) {
            break;
        }

        match_start = (size_t)matches[1].rm_so;
        match_end = (size_t)matches[1].rm_eo;
        consumed = (size_t)matches[0].rm_eo;

        if (match_start > remaining ||
            match_end > remaining ||
            match_end < match_start ||
            consumed > remaining ||
            consumed == 0) {
            break;
        }

        value_length = match_end - match_start;

        if (value_length > 0 &&
            fwrite(buffer + offset + match_start, 1, value_length, stdout) !=
                value_length) {
            break;
        }

        if (fputc('\n', stdout) == EOF) {
            break;
        }

        offset += consumed;
    }

    if (offset >= input_length) {
        result = 0;
    }

    regfree(&regex);
    free(buffer);
    return result;
}

int main(void)
{
    static const char input[] =
        "The values are \"first\", \"second value\", and \"third\".";

    if (extract_quoted_values(input, sizeof(input) - 1) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}