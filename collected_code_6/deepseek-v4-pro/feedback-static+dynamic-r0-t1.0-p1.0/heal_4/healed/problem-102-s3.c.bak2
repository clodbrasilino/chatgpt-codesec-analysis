#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *camel = (char *)malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int capitalize_next = 1;

    if (snake[0] == '_') {
        camel[j++] = '_';
        while (i < len && snake[i] == '_') {
            i++;
        }
        capitalize_next = 1;
    }

    for (; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
        }
    }

    camel[j] = '\0';
    return camel;
}

int main(void) {
    const char *test_cases[] = {
        "snake_case_string",
        "_leading_underscore",
        "trailing_underscore_",
        "multiple__underscores",
        "alreadyCamel",
        "",
        "a",
        "a_b_c_d_e_f",
        NULL
    };
    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t t = 0; t < num_tests; t++) {
        const char *input = test_cases[t];
        char *result = snake_to_camel(input);

        if (input == NULL) {
            printf("NULL -> NULL\n");
        } else {
            if (result != NULL) {
                if (input[0] == '\0') {
                    printf("\"%s\" -> \"%s\"\n", input, result);
                } else {
                    printf("%s -> %s\n", input, result);
                }
                free(result);
            } else {
                printf("%s -> (allocation failed)\n", input);
            }
        }
    }

    return 0;
}