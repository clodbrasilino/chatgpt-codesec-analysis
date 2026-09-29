#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'bc', got <no output>
  *  test case 1 failed: expected '123', got <no output>
  *  test case 0 failed: expected 'abc', got <no output>
  */

char *remove_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != ' ') {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *test_cases[] = {
        "a b c",
        "1 2 3",
        "b c"
    };

    for (int i = 0; i < 3; i++) {
        char *output = remove_spaces(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        }
    }

    return 0;
}