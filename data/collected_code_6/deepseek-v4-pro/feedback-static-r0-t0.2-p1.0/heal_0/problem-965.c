#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t max_len = len * 2 + 1;
    char *result = (char *)malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)input[i])) {
            if (j > 0 && result[j - 1] != '_') {
                result[j++] = '_';
            }
            result[j++] = (char)tolower((unsigned char)input[i]);
        } else {
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
        "",
        "a",
        "A",
        "camelCASE"
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *converted = camel_to_snake(test_cases[i]);
        if (converted != NULL) {
            printf("\"%s\" -> \"%s\"\n", test_cases[i], converted);
            free(converted);
        } else {
            printf("\"%s\" -> NULL\n", test_cases[i]);
        }
    }

    return 0;
}