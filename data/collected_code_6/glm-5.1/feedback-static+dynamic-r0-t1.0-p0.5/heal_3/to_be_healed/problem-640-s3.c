#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got �
  *  test case 0 failed: expected 'python', got 
  *  test case 1 failed: expected 'string', got @
  */

char *remove_parenthesis(const char *str, size_t len) {
    char *result = malloc(len + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    size_t depth = 0;

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

    char *trimmed = malloc(j + 1);
    if (trimmed) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(trimmed, result, j + 1);
        free(result);
        result = trimmed;
    }

    char *shrunk = realloc(result, j + 1);
    if (shrunk) {
        return shrunk;
    }

    return result;
}

int main(void) {
    const char *input = "Hello (World) C (Programming) Language";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *output = remove_parenthesis(input, len);
    
    if (output) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}