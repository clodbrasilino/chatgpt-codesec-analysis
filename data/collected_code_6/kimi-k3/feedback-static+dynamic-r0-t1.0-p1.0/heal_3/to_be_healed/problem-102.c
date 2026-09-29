#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  */

char *snake_to_camel(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int capitalize_next = 0;

    while (i < len) {
        if (input[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                result[j++] = (char)toupper((unsigned char)input[i]);
                capitalize_next = 0;
            } else {
                result[j++] = input[i];
            }
        }
        i++;
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "python_program",
        "python_language",
        "programming_language"
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_tests; i++) {
        char *camel = snake_to_camel(test_cases[i]);
        if (camel != NULL) {
            printf("%s\n", camel);
            free(camel);
        }
    }

    return 0;
}