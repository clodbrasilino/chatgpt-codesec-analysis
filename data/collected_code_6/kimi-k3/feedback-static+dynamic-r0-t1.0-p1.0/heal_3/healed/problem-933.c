#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 1024

char *camel_to_snake(const char *input) {
    if (input == NULL || *input == '\0') {
        return NULL;
    }

    size_t input_len = 0;
    while (input_len < MAX_STRING_LEN && input[input_len] != '\0') {
        input_len++;
    }

    if (input_len == MAX_STRING_LEN && input[input_len] != '\0') {
        return NULL;
    }

    size_t output_len = input_len * 2 + 1;
    char *output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    size_t in_idx = 0;

    while (in_idx < input_len) {
        unsigned char c = (unsigned char)input[in_idx];
        if (isupper(c)) {
            if (in_idx > 0) {
                output[out_idx++] = '_';
            }
            output[out_idx++] = (char)tolower(c);
        } else {
            output[out_idx++] = (char)tolower(c);
        }
        in_idx++;
    }

    output[out_idx] = '\0';

    if (out_idx == 0) {
        free(output);
        return NULL;
    }

    return output;
}

int main(void) {
    const char *test_cases[] = {
        "camelCaseString",
        "anotherExampleHere",
        "simpleTest",
        "XMLHttpRequest",
        "already_snake_case",
        "lowercase",
        "googleAssistant",
        "chromeCast",
        "quadCore",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }

    return 0;
}