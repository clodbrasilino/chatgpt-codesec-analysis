#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LEN 1024

char *snake_to_camel(const char *input, size_t input_len) {
    char *result = NULL;
    size_t result_len = 0;
    size_t i = 0;

    if (input == NULL || input_len == 0) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    while (i < input_len) {
        if (input[i] == '_' && (i + 1) < input_len && islower((unsigned char)input[i + 1])) {
            result[result_len++] = (char)toupper((unsigned char)input[i + 1]);
            i += 2;
        } else {
            result[result_len++] = input[i];
            i++;
        }
    }

    result[result_len] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "hello_world",
        "snake_case_string_example",
        "single",
        "multiple__underscores",
        NULL
    };
    int i;

    for (i = 0; test_cases[i] != NULL; i++) {
        size_t len = strnlen(test_cases[i], MAX_STRING_LEN);
        char *camel = snake_to_camel(test_cases[i], len);
        if (camel != NULL) {
            printf("Input:  %s\n", test_cases[i]);
            printf("Output: %s\n\n", camel);
            free(camel);
        } else {
            printf("Conversion failed for: %s\n\n", test_cases[i]);
        }
    }

    return 0;
}