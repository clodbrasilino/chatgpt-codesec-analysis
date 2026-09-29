#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *remove_lowercase(const char *input) {
    regex_t regex;
    int ret;
    size_t input_len;
    char *result;
    char *result_ptr;
    const char *cursor;
    regmatch_t match[1];

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    input_len = safe_strlen(input, MAX_INPUT_LEN);
    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result[0] = '\0';
    result_ptr = result;
    cursor = input;
    size_t dest_remaining = input_len;

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t prefix_len = (size_t)match[0].rm_so;
        if (prefix_len > 0) {
            if (prefix_len > dest_remaining) {
                prefix_len = dest_remaining;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result_ptr, cursor, prefix_len);
            result_ptr += prefix_len;
            dest_remaining -= prefix_len;
        }
        cursor += match[0].rm_eo;
    }

    size_t remaining_len = safe_strlen(cursor, MAX_INPUT_LEN);
    if (remaining_len > 0) {
        if (remaining_len > dest_remaining) {
            remaining_len = dest_remaining;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result_ptr, cursor, remaining_len);
        result_ptr += remaining_len;
    }
    *result_ptr = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "HelloWorld123ThisIsATest";
    char *processed_str = remove_lowercase(test_str);

    if (processed_str != NULL) {
        printf("%s\n", processed_str);
        free(processed_str);
    } else {
        fprintf(stderr, "Failed to process string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}