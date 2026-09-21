#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <regex.h>

static int extract_quoted_values(const char *input, size_t input_length)
{
    regex_t regex;
    regmatch_t matches[2];
    size_t offset = 0;
    int status;

    if (input == NULL) {
        return -1;
    }

    status = regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (offset < input_length) {
        size_t remaining = input_length - offset;
        regoff_t start;
        regoff_t end;
        regoff_t match_end;
        size_t length;
        char *buffer;

        if (remaining == SIZE_MAX) {
            regfree(&regex);
            return -1;
        }

        buffer = malloc(remaining + 1);
        if (buffer == NULL) {
            regfree(&regex);
            return -1;
        }

        for (size_t i = 0; i < remaining; ++i) {
            buffer[i] = input[offset + i];
        }
        buffer[remaining] = '\0';

        status = regexec(&regex, buffer, 2, matches, 0);
        if (status != 0) {
            free(buffer);
            break;
        }

        start = matches[1].rm_so;
        end = matches[1].rm_eo;
        match_end = matches[0].rm_eo;

        if (start < 0 || end < start || match_end <= 0 ||
            (uintmax_t)end > (uintmax_t)remaining ||
            (uintmax_t)match_end > (uintmax_t)remaining) {
            free(buffer);
            regfree(&regex);
            return -1;
        }

        length = (size_t)(end - start);

        if (fwrite(buffer + (size_t)start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            free(buffer);
            regfree(&regex);
            return -1;
        }

        offset += (size_t)match_end;
        free(buffer);
    }

    regfree(&regex);
    return status == REG_NOMATCH || offset == input_length ? 0 : -1;
}

int main(void)
{
    static const char input[] =
        "name=\"Alice\" city=\"London\" message=\"Hello, world!\"";

    if (extract_quoted_values(input, sizeof(input) - 1) != 0) {
        fputs("Failed to extract quoted values.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}