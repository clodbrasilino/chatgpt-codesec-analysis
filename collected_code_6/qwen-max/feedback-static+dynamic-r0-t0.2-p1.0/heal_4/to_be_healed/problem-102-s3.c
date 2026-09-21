#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  */

char* snake_to_camel(char *snake_str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = malloc(strlen(snake_str) + 1);
    if (result == NULL) return NULL;
    char *p = snake_str;
    char *new_p = result;
    int capitalize_next = 1;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
        } else {
            if (capitalize_next || new_p == result) {
                *new_p = toupper((unsigned char)*p);
                capitalize_next = 0;
            } else {
                *new_p = *p;
            }
            new_p++;
            p++;
        }
    }
    *new_p = '\0';

    free(snake_str);
    return result;
}

int main() {
    char *snake_case1 = strdup("python_program");
    char *snake_case2 = strdup("python_language");
    char *snake_case3 = strdup("programming_language");

    printf("%s\n", snake_to_camel(snake_case1));
    printf("%s\n", snake_to_camel(snake_case2));
    printf("%s\n", snake_to_camel(snake_case3));

    /* Possible weaknesses found:
     *  Memory leak: snake_case2 [memleak]
     *  Memory leak: snake_case1 [memleak]
     *  Memory leak: snake_case3 [memleak]
     */
    return 0;
}