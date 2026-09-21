#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 8192

static size_t get_safe_length(const char* str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* convert_camel_to_snake(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = get_safe_length(input, MAX_INPUT_LEN);
    size_t max_out_len = len * 2 + 1;
    
    char* result = (char*)malloc(max_out_len);
    if (result == NULL) {
        return NULL;
    }

    char* out = result;
    for (size_t i = 0; i < len; ++i) {
        if (isupper((unsigned char)input[i])) {
            if (i > 0) {
                *out++ = '_';
            }
            *out++ = tolower((unsigned char)input[i]);
        } else {
            *out++ = tolower((unsigned char)input[i]);
        }
    }
    *out = '\0';

    return result;
}

int main(void) {
    const char* test_cases[] = {
        "camelCaseString",
        "PascalCaseString",
        "already_snake_case",
        "simple",
        "",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; ++i) {
        if (test_cases[i] != NULL) {
            char* snake_case_str = convert_camel_to_snake(test_cases[i]);
            if (snake_case_str != NULL) {
                printf("%s\n", snake_case_str);
                free(snake_case_str);
            } else {
                fprintf(stderr, "Failed to convert string or allocate memory.\n");
            }
        }
    }

    return 0;
}