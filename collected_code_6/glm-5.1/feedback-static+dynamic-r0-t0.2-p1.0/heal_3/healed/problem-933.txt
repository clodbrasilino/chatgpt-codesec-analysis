#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    char *result = malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i != 0) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            result[j++] = camel_str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "GoogleAssistant",
        "ChromeCast",
        "QuadCore",
        "convertCamelCaseToSnakeCase",
        "google_assistant",
        "chrome_cast",
        "quad_core",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            fprintf(stderr, "Conversion failed\n");
            return 1;
        }
    }

    return 0;
}