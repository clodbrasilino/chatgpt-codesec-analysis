#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 0 failed: expected 'python', got <no output>
  */

char *remove_parenthesis(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    size_t j = 0;
    int depth = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            } else {
                result[j++] = str[i];
            }
        } else {
            if (depth == 0) {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';
    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }
    return result;
}

int main(void) {
    const char *inputs[] = {"(python)", "this is a (string)", "alpha (beta) gamma"};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    
    for (size_t k = 0; k < num_inputs; k++) {
        char *output = remove_parenthesis(inputs[k]);
        if (output == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        printf("%s\n", output);
        free(output);
    }
    
    return 0;
}