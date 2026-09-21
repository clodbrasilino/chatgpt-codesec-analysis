#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_SIZE 4096

char *filter_alnum_regex(const char *input);

char *filter_alnum_regex(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'input_len<4096' is not redundant
     *  Either the condition 'input_len<4096' is redundant or the array 'input[26]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (input_len < MAX_INPUT_SIZE && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len == MAX_INPUT_SIZE) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *dest = result;
    size_t dest_capacity = input_len;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t len = match[0].rm_eo - match[0].rm_so;
        
        if (len == 0 || len > dest_capacity) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, cursor + match[0].rm_so, len);
        dest += len;
        dest_capacity -= len;
        cursor += match[0].rm_eo;
    }
    *dest = '\0';

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