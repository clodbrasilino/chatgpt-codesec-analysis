#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *str) {
    size_t len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int j = 0;
    int uppercase_next = 1;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '_') {
            uppercase_next = 1;
        } else {
            result[j++] = uppercase_next ? toupper((unsigned char)str[i]) : tolower((unsigned char)str[i]);
            uppercase_next = 0;
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *inputs[] = {
        "python_program",
        "python_language",
        "programming_language"
    };
    const char *expected[] = {
        "PythonProgram",
        "PythonLanguage",
        "ProgrammingLanguage"
    };

    for (size_t k = 0; k < sizeof(inputs) / sizeof(inputs[0]); ++k) {
        char *output = snake_to_camel(inputs[k]);
        if (output != NULL) {
            printf("Camel case: %s\n", output);
            if (strcmp(output, expected[k]) != 0) {
                printf("Test case %zu failed: expected '%s', got '%s'\n", k, expected[k], output);
            }
            free(output);
        } else {
            printf("Memory allocation failed.\n");
        }
    }

    return 0;
}