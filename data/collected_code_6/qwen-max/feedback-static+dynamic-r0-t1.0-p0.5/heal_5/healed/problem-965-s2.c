#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* camel_to_snake(const char *str) {
    if (str == NULL) return NULL;

    int len = 0;
    const char *p = str;
    while (*p) {
        len++;
        p++;
    }

    char *result = (char *)malloc((len * 2 + 2) * sizeof(char));
    if (result == NULL) return NULL;

    int i = 0;
    for (int j = 0; str[j]; j++) {
        if (isupper((unsigned char)str[j])) {
            if (i > 0 && result[i-1] != '_') {
                result[i++] = '_';
            }
            result[i++] = tolower((unsigned char)str[j]);
        } else {
            result[i++] = str[j];
        }
    }
    result[i] = '\0';

    return result;
}

int main() {
    const char *test_cases[] = {"PythonProgram", "PythonLanguage", "ProgrammingLanguage"};
    const char *expected_outputs[] = {"python_program", "python_language", "programming_language"};
    int num_test_cases = 3;

    for (int k = 0; k < num_test_cases; k++) {
        char *output = camel_to_snake(test_cases[k]);
        if (output != NULL) {
            if (strcmp(output, expected_outputs[k]) == 0) {
                printf("Test case %d passed: %s\n", k, output);
            } else {
                printf("Test case %d failed: expected '%s', got '%s'\n", k, expected_outputs[k], output);
            }
            free(output);
        } else {
            printf("Error: Output is NULL for test case %d\n", k);
        }
    }

    return 0;
}