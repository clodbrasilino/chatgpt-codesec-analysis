#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

void filter_alphanumeric(const char *input, char **output) {
    if (input == NULL || output == NULL) {
        return;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        *output = NULL;
        return;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        regfree(&regex);
        *output = NULL;
        return;
    }

    *output = (char *)malloc(len + 1);
    if (*output == NULL) {
        regfree(&regex);
        return;
    }

    regmatch_t pmatch[1];
    const char *p = input;
    char *out_p = *output;
    size_t remaining_out = len + 1;

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        size_t match_start = pmatch[0].rm_so;
        size_t match_end = pmatch[0].rm_eo;

        if (match_start >= remaining_out) {
            match_start = remaining_out - 1;
        }

        if (match_start > 0) {
            memcpy(out_p, p, match_start);
            out_p += match_start;
            remaining_out -= match_start;
        }
        p += match_end;
    }

    size_t p_len = strnlen(p, remaining_out);
    if (p_len >= remaining_out) {
        p_len = remaining_out - 1;
    }
    
    if (p_len > 0) {
        memcpy(out_p, p, p_len);
        out_p += p_len;
    }
    *out_p = '\0';
    
    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output = NULL;

    filter_alphanumeric(input, &output);

    if (output != NULL) {
        printf("Original: %s\n", input);
        printf("Filtered: %s\n", output);
        free(output);
    } else {
        printf("Error processing string.\n");
    }

    return 0;
}