#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) return NULL;

    size_t len = 0;
    while (input[len] != '\0') len++;

    char *output = (char *)malloc((len + 2) * sizeof(char));
    if (output == NULL) return NULL;

    int j = 0;
    for (int i = 0; i < len; ++i) {
        if (isupper(input[i])) {
            if (i > 0 && !isupper(input[i - 1]) && input[i - 1] != '_') {
                output[j++] = '_';
            }
            output[j++] = tolower(input[i]);
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';

    return output;
}

int main() {
    const char *test_cases[] = {
        "PythonProgram",
        "PythonLanguage",
        "ProgrammingLanguage",
        "ThisIsCamelCase"
    };

    const char *expected_outputs[] = {
        "python_program",
        "python_language",
        "programming_language",
        "this_is_camel_case"
    };

    for (size_t k = 0; k < sizeof(test_cases) / sizeof(test_cases[0]); ++k) {
        char *result = camel_to_snake(test_cases[k]);

        if (result != NULL) {
            if (strcmp(result, expected_outputs[k]) == 0) {
                printf("%s\n", result);
            } else {
                printf("Test case %zu failed: expected '%s', got '%s'\n", k, expected_outputs[k], result);
            }
            free(result);
        } else {
            printf("Conversion failed.\n");
        }
    }

    return 0;
}