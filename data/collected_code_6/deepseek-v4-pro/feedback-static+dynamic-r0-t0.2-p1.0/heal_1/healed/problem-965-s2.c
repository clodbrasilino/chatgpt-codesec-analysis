#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
        if (len > 4096) {
            return NULL;
        }
    }

    size_t max_len = len * 2 + 1;
    char *result = (char *)malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)input[i];
        if (isupper(ch)) {
            if (j > 0 && result[j - 1] != '_') {
                if (j + 2 >= max_len) {
                    free(result);
                    return NULL;
                }
                result[j++] = '_';
            }
            if (j + 1 >= max_len) {
                free(result);
                return NULL;
            }
            result[j++] = (char)tolower(ch);
        } else {
            if (j + 1 >= max_len) {
                free(result);
                return NULL;
            }
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "camelCase",
        "CamelCase",
        "camel",
        "already_snake",
        "HTTPServer",
        "camelCaseString",
        "a",
        "A",
        "",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *snake = camel_to_snake(test_cases[i]);
        if (snake != NULL) {
            printf("%s -> %s\n", test_cases[i], snake);
            free(snake);
        } else {
            printf("%s -> (null)\n", test_cases[i]);
        }
    }

    return 0;
}