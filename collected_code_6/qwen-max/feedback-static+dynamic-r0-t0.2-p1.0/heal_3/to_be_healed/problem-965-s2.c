#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) return NULL;

    int len = strlen(input);
    char *output = (char *)malloc((len + 1) * sizeof(char));
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
    const char *test_cases[] = {"ThisIsCamelCase", "PythonProgram", "PythonLanguage", "ProgrammingLanguage"};
    const char *expected_outputs[] = {"this_is_camel_case", "python_program", "python_language", "programming_language"};
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; ++i) {
        char *result = camel_to_snake(test_cases[i]);
        if (result != NULL) {
            if (strcmp(result, expected_outputs[i]) != 0) {
                printf("Test case %d failed: expected '%s', got '%s'\n", i, expected_outputs[i], result);
            } else {
                printf("Converted: %s\n", result);
            }
            free(result);
        } else {
            printf("Conversion failed for test case %d: %s\n", i, test_cases[i]);
        }
    }

    return 0;
}