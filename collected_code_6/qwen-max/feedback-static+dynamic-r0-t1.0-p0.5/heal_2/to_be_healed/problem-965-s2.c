#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char* camel_to_snake(const char *str) {
    if (str == NULL) return NULL;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    char *result = (char *)malloc(len * 2 + 1);
    if (result == NULL) return NULL;

    int i = 0;
    const char *p = str;

    while (*p) {
        if (isupper((unsigned char)*p)) {
            if (i > 0 && result[i-1] != '_') {
                result[i++] = '_';
            }
            result[i++] = tolower((unsigned char)*p);
        } else {
            result[i++] = *p;
        }
        p++;
    }
    result[i] = '\0';

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'input' can be declared as const array [constVariable]
     */
    char input[] = "ThisIsCamelCase";
    char *output = camel_to_snake(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }
    return 0;
}