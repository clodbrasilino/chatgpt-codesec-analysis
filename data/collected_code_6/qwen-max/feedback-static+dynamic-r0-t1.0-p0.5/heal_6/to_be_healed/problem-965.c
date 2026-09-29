#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char *camel_to_snake(const char *str) {
    if (str == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i - 1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    const char *input[] = {"pythonProgram", "PythonLanguage", "ProgrammingLanguage"};
    const char *expected_output[] = {"python_program", "python_language", "programming_language"};
    for (int k = 0; k < 3; k++) {
        char *output = camel_to_snake(input[k]);
        if (output != NULL) {
            printf("Expected: %s, Got: %s\n", expected_output[k], output);
            free(output);
        } else {
            printf("Failed to convert %s\n", input[k]);
        }
    }
    return 0;
}