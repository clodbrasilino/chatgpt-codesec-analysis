#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  */

char* remove_parenthesis_area(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;
    int result_index = 0;
    int depth = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) depth--;
        } else if (depth == 0) {
            result[result_index++] = str[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char input[] = "This is a (test string with (nested) parentheses)";
    char *output = remove_parenthesis_area(input);

    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}