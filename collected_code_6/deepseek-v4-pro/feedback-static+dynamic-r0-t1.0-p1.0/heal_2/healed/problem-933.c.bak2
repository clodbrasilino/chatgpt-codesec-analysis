#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    size_t input_len = strlen(input);
    size_t output_len = input_len + 1;
    size_t i, j;
    char *output;
    int prev_lower = 0;

    if (input_len == 0) {
        output = (char *)malloc(1);
        if (output != NULL) {
            output[0] = '\0';
        }
        return output;
    }

    for (i = 0; i < input_len; i++) {
        if (isupper(input[i]) && i > 0 && prev_lower) {
            output_len++;
        }
        prev_lower = islower(input[i]) || isdigit(input[i]) || input[i] == '_';
    }

    output = (char *)malloc(output_len);
    if (output == NULL) {
        return NULL;
    }

    j = 0;
    prev_lower = 0;

    for (i = 0; i < input_len; i++) {
        if (isupper(input[i]) && i > 0 && prev_lower) {
            output[j++] = '_';
        }
        output[j++] = tolower(input[i]);
        prev_lower = islower(input[i]) || isdigit(input[i]) || input[i] == '_';
    }

    output[j] = '\0';
    return output;
}

int main(void) {
    const char *tests[] = {
        "chromeCast",
        "googleAssistant",
        "quadCore",
        "camelCase",
        "helloWorld",
        "thisIsATest",
        "already_snake",
        "mixedCase_WithSnake",
        "UPPERCASE",
        "camel123Case",
        "c"
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