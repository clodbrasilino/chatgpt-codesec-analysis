#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* snake_to_camel(const char *snake_str) {
    size_t len = strlen(snake_str);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }
    int index = 0, capitalize_next = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (i < len && snake_str[i] == '_') {
            capitalize_next = 1;
        } else if (capitalize_next && isalpha(snake_str[i])) {
            output[index++] = toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            output[index++] = snake_str[i];
        }
    }
    output[len] = '\0';
    return output;
}

int main() {
    const char *test_cases[] = {
        "python_program",
        "python_language",
        "programming_language"
    };
    const char *expected_results[] = {
        "PythonProgram",
        "PythonLanguage",
        "ProgrammingLanguage"
    };
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; ++i) {
        char *result = snake_to_camel(test_cases[i]);
        if (result != NULL) {
            printf("Test %d: %s\n", i, result);
            if (strcmp(result, expected_results[i]) != 0) {
                printf("  Expected: %s\n", expected_results[i]);
            }
            free(result);
        }
    }

    return 0;
}