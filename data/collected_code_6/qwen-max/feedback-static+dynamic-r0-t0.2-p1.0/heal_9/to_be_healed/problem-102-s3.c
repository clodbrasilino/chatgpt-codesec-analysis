#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  */

char* snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) return NULL;
    size_t len = 0;
    while (snake_str[len] != '\0' && snake_str[len] != '_') len++;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    char *result = malloc(strlen(snake_str) - len + 2);
    if (result == NULL) return NULL;
    const char *p = snake_str;
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

    return result;
}

int main() {
    const char *snake_case1 = "python_program";
    const char *snake_case2 = "python_language";
    const char *snake_case3 = "programming_language";

    char *camel_case1 = snake_to_camel(snake_case1);
    char *camel_case2 = snake_to_camel(snake_case2);
    char *camel_case3 = snake_to_camel(snake_case3);

    printf("%s\n", camel_case1 ? camel_case1 : "<no output>");
    printf("%s\n", camel_case2 ? camel_case2 : "<no output>");
    printf("%s\n", camel_case3 ? camel_case3 : "<no output>");

    free(camel_case1);
    free(camel_case2);
    free(camel_case3);

    return 0;
}