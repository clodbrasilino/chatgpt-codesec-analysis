#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        char *output = (char *)malloc(1);
        if (output != NULL) {
            output[0] = '\0';
        }
        return output;
    }

    size_t output_len = input_len + 1;
    size_t i;

    for (i = 1; i < input_len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (islower((unsigned char)input[i - 1]) || 
                isdigit((unsigned char)input[i - 1])) {
                output_len++;
            }
        }
    }

    char *output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;

    output[out_idx++] = tolower((unsigned char)input[0]);

    for (i = 1; i < input_len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (islower((unsigned char)input[i - 1]) || 
                isdigit((unsigned char)input[i - 1])) {
                output[out_idx++] = '_';
            }
        }
        output[out_idx++] = tolower((unsigned char)input[i]);
    }

    output[out_idx] = '\0';

    return output;
}

int main(void) {
    const char *tests[] = {
        "camelCase",
        "helloWorld",
        "thisIsATest",
        "already_snake",
        "mixedCase_WithSnake",
        "UPPERCASE",
        "camel123Case",
        "c",
        "chromeCast",
        "googleAssistant",
        "quadCore"
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result != NULL) {
            printf("%s -> %s\n", tests[i], result);
            free(result);
        } else {
            printf("%s -> (conversion failed)\n", tests[i]);
        }
    }

    return 0;
}