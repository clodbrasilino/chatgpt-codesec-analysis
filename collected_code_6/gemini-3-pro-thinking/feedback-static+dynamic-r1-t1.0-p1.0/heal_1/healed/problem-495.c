#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *input) {
    regex_t regex;
    int ret;
    size_t input_len = 0;
    char *result;
    char *result_ptr;
    const char *cursor;
    regmatch_t match[1];

    if (input == NULL) {
        return NULL;
    }

    while (input[input_len] != '\0') {
        input_len++;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result[0] = '\0';
    result_ptr = result;
    cursor = input;

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t prefix_len = (size_t)match[0].rm_so;
        if (prefix_len > 0 && (size_t)(result_ptr - result) + prefix_len <= input_len) {
            size_t i;
            for (i = 0; i < prefix_len; i++) {
                result_ptr[i] = cursor[i];
            }
            result_ptr += prefix_len;
        }
        cursor += match[0].rm_eo;
    }

    size_t remaining_len = input_len - (size_t)(cursor - input);
    if (remaining_len > 0 && (size_t)(result_ptr - result) + remaining_len <= input_len) {
        size_t i;
        for (i = 0; i < remaining_len; i++) {
            result_ptr[i] = cursor[i];
        }
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