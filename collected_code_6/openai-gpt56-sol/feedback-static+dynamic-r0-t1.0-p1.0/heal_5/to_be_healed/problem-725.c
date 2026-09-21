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
    int result = -1;
    int status;

    if (input == NULL || input_length > SIZE_MAX - 1) {
        return -1;
    }

    buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        return -1;
    }

    if (input_length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
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
        size_t start;
        size_t end;
        size_t consumed;
        size_t length;

        status = regexec(&regex, buffer + offset, 2, matches, 0);
        if (status == REG_NOMATCH) {
            result = 0;
            break;
        }
        if (status != 0) {
            break;
        }

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so ||
            matches[1].rm_so < 0 ||
            matches[1].rm_eo < matches[1].rm_so) {
            break;
        }

        start = (size_t)matches[1].rm_so;
        end = (size_t)matches[1].rm_eo;
        consumed = (size_t)matches[0].rm_eo;

        if (start > remaining ||
            end > remaining ||
            end < start ||
            consumed > remaining ||
            consumed == 0) {
            break;
        }

        length = end - start;

        if (length > 0 &&
            fwrite(buffer + offset + start, 1, length, stdout) != length) {
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