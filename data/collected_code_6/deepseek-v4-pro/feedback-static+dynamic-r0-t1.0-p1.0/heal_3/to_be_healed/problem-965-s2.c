#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 4096);
    size_t max_size = len * 2 + 1;
    char *result = (char *)malloc(max_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int last_was_underscore = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (c == '_') {
            if (j < max_size - 1) {
                result[j++] = '_';
            }
            last_was_underscore = 1;
        } else if (isupper(c)) {
            if (j > 0 && !last_was_underscore && result[j - 1] != '_') {
                if (j < max_size - 1) {
                    result[j++] = '_';
                }
            }
            if (j < max_size - 1) {
                result[j++] = (char)tolower(c);
            }
            last_was_underscore = 0;
        } else {
            if (j < max_size - 1) {
                result[j++] = c;
            }
            last_was_underscore = 0;
        }
    }

    if (j < max_size) {
        result[j] = '\0';
    } else {
        result[max_size - 1] = '\0';
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "camelCase",
        "PascalCase",
        "already_snake",
        "ABC",
        "aBc",
        "",
        "helloWorldExample",
        "CamelCaseTest123",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        char *converted = camel_to_snake(tests[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", tests[i], converted);
            free(converted);
        } else {
            printf("%s -> (null)\n", tests[i]);
        }
    }

    return 0;
}