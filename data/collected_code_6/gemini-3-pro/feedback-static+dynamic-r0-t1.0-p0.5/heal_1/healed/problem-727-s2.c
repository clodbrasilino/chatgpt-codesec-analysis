#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_special_chars(const char *input, size_t max_len, char **output) {
    if (!input || !output || max_len == 0) {
        return -1;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    size_t len = strnlen(input, max_len);
    *output = (char *)malloc(len + 1);
    if (!*output) {
        regfree(&regex);
        return -1;
    }

    size_t out_idx = 0;
    regmatch_t pmatch[1];
    const char *cursor = input;
    size_t remaining = len;

    while (remaining > 0 && regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start > remaining) match_start = remaining;

        for (size_t i = 0; i < match_start; ++i) {
            (*output)[out_idx++] = cursor[i];
        }

        if (match_end > remaining) match_end = remaining;
        cursor += match_end;
        remaining -= match_end;
    }

    while (remaining > 0 && *cursor != '\0') {
        (*output)[out_idx++] = *cursor++;
        remaining--;
    }

    (*output)[out_idx] = '\0';

    regfree(&regex);
    return 0;
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;
    size_t max_len = 1024;

    if (remove_special_chars(input, max_len, &output) == 0) {
        printf("Original: %s\n", input);
        printf("Cleaned:  %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}