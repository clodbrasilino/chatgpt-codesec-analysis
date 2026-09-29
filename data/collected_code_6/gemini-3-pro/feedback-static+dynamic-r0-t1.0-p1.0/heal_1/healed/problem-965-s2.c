#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camel_to_snake(const char* camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t length = 0;
    size_t snake_length = 0;
    for (size_t i = 0; camel_case[i] != '\0'; i++) {
        length++;
        snake_length++;
        if (isupper((unsigned char)camel_case[i]) && i > 0) {
            snake_length++;
        }
    }

    if (length == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    char* snake_case = (char*)malloc(snake_length + 1);
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)camel_case[i])) {
            if (i > 0) {
                snake_case[j++] = '_';
            }
            snake_case[j++] = tolower((unsigned char)camel_case[i]);
        } else {
            snake_case[j++] = camel_case[i];
        }
    }
    snake_case[j] = '\0';

    return snake_case;
}

int main(void) {
    const char* test_strings[] = {
        "camelCase",
        "thisIsATestString",
        "already_snake",
        "PascalCase",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char* result = camel_to_snake(test_strings[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else if (test_strings[i] == NULL) {
            printf("(null)\n");
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}