#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  */

char* camel_to_snake(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t result_len = len * 2 + 1; // Maximum possible length
    char *result = (char *)malloc(result_len * sizeof(char));
    if (!result) {
        return NULL;
    }
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && str[i-1] != '_') {
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
    const char input[] = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}