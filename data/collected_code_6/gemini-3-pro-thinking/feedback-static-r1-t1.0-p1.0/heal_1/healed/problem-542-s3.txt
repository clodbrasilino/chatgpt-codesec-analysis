#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

char *replace_chars_with_colon(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[ ,.]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strnlen(input, MAX_INPUT_LEN);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[1];
    const char *cursor = input;
    char *out_cursor = output;
    size_t remaining = len + 1;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;

        if (prefix_len >= remaining) {
            prefix_len = remaining - 1;
        }

        snprintf(out_cursor, remaining, "%.*s", (int)prefix_len, cursor);
        out_cursor += prefix_len;
        remaining -= prefix_len;

        if (remaining > 1) {
            *out_cursor = ':';
            out_cursor++;
            remaining--;
        }

        cursor += pmatch[0].rm_eo;
    }

    snprintf(out_cursor, remaining, "%s", cursor);
    regfree(&regex);

    return output;
}

int main(void) {
    const char *test_str = "Hello, world. This is a test string.";
    char *result = replace_chars_with_colon(test_str);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}