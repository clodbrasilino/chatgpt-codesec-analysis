#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1000000

int remove_non_alnum(const char *input, char **output) {
    if (!input || !output) {
        return -1;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
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
    size_t remaining_out = len + 1;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = (size_t)pmatch[0].rm_so;
        size_t match_end = (size_t)pmatch[0].rm_eo;

        if (match_start > 0) {
            if (match_start >= remaining_out) {
                match_start = remaining_out - 1;
            }
            for (size_t i = 0; i < match_start; i++) {
                out_cursor[i] = cursor[i];
            }
            out_cursor += match_start;
            remaining_out -= match_start;
        }

        if (match_end == match_start) {
            match_end++;
        }
        cursor += match_end;
    }

    size_t cursor_len = strnlen(cursor, remaining_out);
    if (cursor_len >= remaining_out) {
        cursor_len = remaining_out - 1;
    }
    
    if (cursor_len > 0) {
        for (size_t i = 0; i < cursor_len; i++) {
            out_cursor[i] = cursor[i];
        }
        out_cursor += cursor_len;
    }
    *out_cursor = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    if (remove_non_alnum(input, &output) == 0) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}