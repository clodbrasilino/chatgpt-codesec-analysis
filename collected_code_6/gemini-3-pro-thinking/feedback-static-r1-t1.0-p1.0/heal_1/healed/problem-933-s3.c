#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camel_to_snake(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    size_t underscores = 0;

    for (size_t i = 0; input[i] != '\0'; i++) {
        len++;
        if (i > 0 && isupper((unsigned char)input[i]) && islower((unsigned char)input[i - 1])) {
            underscores++;
        }
    }

    char* output = (char*)malloc(len + underscores + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t out_idx = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)input[i]) && islower((unsigned char)input[i - 1])) {
            output[out_idx++] = '_';
        }
        output[out_idx++] = (char)tolower((unsigned char)input[i]);
    }
    output[out_idx] = '\0';

    return output;
}

int main(void) {
    const char* test_strings[] = {
        "camelCase",
        "CamelCase",
        "myHTMLParser",
        "simpleTestString",
        ""
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char* snake = camel_to_snake(test_strings[i]);
        if (snake != NULL) {
            printf("%s\n", snake);
            free(snake);
        }
    }

    return 0;
}