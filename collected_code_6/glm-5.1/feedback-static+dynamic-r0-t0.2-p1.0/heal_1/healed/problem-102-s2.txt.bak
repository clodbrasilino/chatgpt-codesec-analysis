#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    if (len > 0 && islower((unsigned char)snake_str[0])) {
        camel_str[j++] = (char)toupper((unsigned char)snake_str[0]);
    }

    for (size_t i = 1; i < len; i++) {
        if (snake_str[i - 1] == '_' && islower((unsigned char)snake_str[i])) {
            camel_str[j++] = (char)toupper((unsigned char)snake_str[i]);
        } else if (snake_str[i] != '_') {
            camel_str[j++] = snake_str[i];
        }
    }

    camel_str[j] = '\0';
    return camel_str;
}

int main(void) {
    const char *test_cases[] = {
        "python_program",
        "python_language",
        "programming_language"
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *output = snake_to_camel(test_cases[i]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }

    return 0;
}