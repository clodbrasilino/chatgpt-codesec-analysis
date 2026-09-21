#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1048576

int remove_non_alphanumeric(const char *input, char **output) {
    if (!input || !output) {
        return -1;
    }

    regex_t regex;
    if (regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED) != 0) {
        return -1;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        regfree(&regex);
        return -1;
    }

    *output = (char *)malloc(len + 1);
    if (!*output) {
        regfree(&regex);
        return -1;
    }

    regmatch_t pmatch[1];
    const char *cursor = input;
    char *out_cursor = *output;
    size_t out_capacity = len + 1;
    size_t out_len = 0;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start > 0) {
            if (out_len + match_start < out_capacity) {
                memcpy(out_cursor, cursor, match_start);
                out_cursor += match_start;
                out_len += match_start;
            } else {
                free(*output);
                *output = NULL;
                regfree(&regex);
                return -1;
            }
        }
        cursor += match_end;
    }

    size_t remaining = strnlen(cursor, MAX_INPUT_LEN - (cursor - input));
    if (remaining > 0) {
        if (out_len + remaining < out_capacity) {
            memcpy(out_cursor, cursor, remaining);
            out_cursor += remaining;
        } else {
            free(*output);
            *output = NULL;
            regfree(&regex);
            return -1;
        }
    }

    *out_cursor = '\0';
    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_non_alphanumeric(input, &output) == 0) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}