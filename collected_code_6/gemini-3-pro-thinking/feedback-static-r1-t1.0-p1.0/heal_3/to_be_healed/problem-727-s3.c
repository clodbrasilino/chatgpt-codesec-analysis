#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *filter_alnum_regex(const char *input);

char *filter_alnum_regex(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t max_len = 1048576;
    size_t input_len = 0;
    
    while (input_len < max_len && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len == max_len) {
        regfree(&regex);
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    size_t out_idx = 0;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t len = (size_t)(match[0].rm_eo - match[0].rm_so);
        
        if (len == 0) {
            break;
        }

        if (out_idx + len > input_len) {
            len = input_len - out_idx;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_idx, cursor + match[0].rm_so, len);
            out_idx += len;
        }

        cursor += match[0].rm_eo;
    }
    
    result[out_idx] = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello, World! 123 @#Test.";
    char *cleaned_str = filter_alnum_regex(test_str);

    if (cleaned_str != NULL) {
        printf("%s\n", cleaned_str);
        free(cleaned_str);
    } else {
        fprintf(stderr, "Processing failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}