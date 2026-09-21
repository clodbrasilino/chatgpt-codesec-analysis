#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int extract_quoted_values(const char *input, size_t input_size)
{
    static const char pattern[] = "\"([^\"]*)\"";
    regex_t regex;
    regmatch_t matches[2];
    char *buffer;
    size_t offset = 0;
    int status;
    int result = -1;

    if (input == NULL || input_size > SIZE_MAX - 1) {
        return -1;
    }

    buffer = malloc(input_size + 1);
    if (buffer == NULL) {
        return -1;
    }

    if (input_size != 0) {
        memcpy(buffer, input, input_size);
    }
    buffer[input_size] = '\0';

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        free(buffer);
        return -1;
    }

    while (offset < input_size) {
        const size_t remaining = input_size - offset;
        size_t start;
        size_t end;
        size_t match_end;
        size_t length;

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

        start = (size_t)matches[1].rm_so;
        end = (size_t)matches[1].rm_eo;
        match_end = (size_t)matches[0].rm_eo;

        if (start > remaining ||
            end > remaining ||
            match_end > remaining ||
            end < start ||
            match_end == 0) {
            break;
        }

        length = end - start;

        if (length != 0 &&
            fwrite(buffer + offset + start, 1, length, stdout) != length) {
            break;
        }

        if (fputc('\n', stdout) == EOF) {
            break;
        }

        offset += match_end;
    }

    if (offset == input_size) {
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