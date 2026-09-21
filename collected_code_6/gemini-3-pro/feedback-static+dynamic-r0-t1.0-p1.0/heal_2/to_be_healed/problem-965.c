#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char* camel_to_snake(const char* camel_case) {
    if (camel_case == NULL) {
        return NULL;
    }

    size_t len = 0;
    size_t snake_len = 0;

    for (size_t i = 0; camel_case[i] != '\0'; i++) {
        len++;
        if (isupper((unsigned char)camel_case[i])) {
            snake_len += (i > 0) ? 2 : 1;
        } else {
            snake_len += 1;
        }
    }

    if (len == 0) {
        char* empty_str = (char*)malloc(1);
        if (empty_str != NULL) {
            empty_str[0] = '\0';
        }
        return empty_str;
    }

    char* snake_case = (char*)malloc(snake_len + 1);
    if (snake_case == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
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
        "CamelCase",
        "camelCaseStringHere",
        "already_snake",
        "A",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char* snake = camel_to_snake(test_strings[i]);
        if (snake != NULL) {
            printf("Camel: %s -> Snake: %s\n", test_strings[i] ? test_strings[i] : "NULL", snake);
            free(snake);
        } else {
            printf("Camel: %s -> Snake: (allocation failed or NULL input)\n", test_strings[i] ? test_strings[i] : "NULL");
        }
    }

    return 0;
}