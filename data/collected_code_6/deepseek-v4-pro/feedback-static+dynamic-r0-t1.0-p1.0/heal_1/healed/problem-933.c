#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t output_len = input_len + 1;
    size_t i;

    for (i = 0; i < input_len; i++) {
        if (i > 0 && islower(input[i - 1]) && isupper(input[i])) {
            output_len++;
        }
        if (i > 0 && isdigit(input[i - 1]) && isupper(input[i])) {
            output_len++;
        }
    }

    char *output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;

    for (i = 0; i < input_len; i++) {
        if (i > 0 && islower(input[i - 1]) && isupper(input[i])) {
            output[out_idx++] = '_';
        } else if (i > 0 && isdigit(input[i - 1]) && isupper(input[i])) {
            output[out_idx++] = '_';
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