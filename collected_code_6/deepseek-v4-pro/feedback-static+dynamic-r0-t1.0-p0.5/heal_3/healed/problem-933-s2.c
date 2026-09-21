#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    if (input[0] == '\0') {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }

    size_t max_output_len = input_len * 2 + 1;
    char *result = malloc(max_output_len);
    if (result == NULL) {
        return NULL;
    }

    size_t dst_pos = 0;
    size_t i = 0;

    while (i < input_len) {
        if (isupper((unsigned char)input[i]) && i > 0) {
            if (dst_pos > 0 && result[dst_pos - 1] != '_' && 
                islower((unsigned char)input[i - 1])) {
                result[dst_pos++] = '_';
            } else if (dst_pos > 0 && isdigit((unsigned char)input[i - 1])) {
                result[dst_pos++] = '_';
            } else if (i + 1 < input_len && islower((unsigned char)input[i + 1])) {
                if (dst_pos > 0 && result[dst_pos - 1] != '_') {
                    result[dst_pos++] = '_';
                }
            }
        }

        result[dst_pos++] = tolower((unsigned char)input[i]);
        i++;
    }

    result[dst_pos] = '\0';

    char *final_result = realloc(result, dst_pos + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }

    return final_result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "thisIsATest",
        "already_snake",
        "ABC",
        "aB",
        "helloWorld123",
        "quad_core",
        "google_assistant",
        "chrome_cast",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("%s -> conversion failed\n", test_cases[i]);
        }
    }

    return 0;
}