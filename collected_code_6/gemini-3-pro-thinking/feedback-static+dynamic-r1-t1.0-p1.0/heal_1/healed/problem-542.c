#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 1048576

char *replace_characters_with_colon(const char *input) {
    regex_t regex;
    int ret;
    size_t len;
    char *result;
    const char *cursor;
    char *out_cursor;
    regmatch_t pmatch[1];
    size_t remaining;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    out_cursor = result;
    remaining = len + 1;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len;

        if (pmatch[0].rm_so < 0 || pmatch[0].rm_eo < 0) {
            break;
        }

        prefix_len = (size_t)pmatch[0].rm_so;

        if (prefix_len > 0) {
            if (prefix_len >= remaining) {
                prefix_len = remaining - 1;
            }
            memcpy(out_cursor, cursor, prefix_len);
            out_cursor += prefix_len;
            remaining -= prefix_len;
        }

        if (remaining > 1) {
            *out_cursor = ':';
            out_cursor++;
            remaining--;
        }

        cursor += pmatch[0].rm_eo;
    }

    if (remaining > 0) {
        snprintf(out_cursor, remaining, "%s", cursor);
    }

    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "This is a test, with spaces. and commas, and dots.";
    char *replaced_string;

    replaced_string = replace_characters_with_colon(test_string);

    if (replaced_string != NULL) {
        printf("%s\n", replaced_string);
        free(replaced_string);
        replaced_string = NULL;
    }

    return 0;
}