#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got python_anguage
  *  test case 0 failed: expected 'PythonProgram', got python_rogram
  *  test case 2 failed: expected 'ProgrammingLanguage', got programming_anguage
  */

char* snake_to_camel(char *snake_case) {
    char *token = strstr(snake_case, "_");
    while (token != NULL) {
        token++;
        *token = toupper(*token);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        memmove(token, token + 1, strlen(token));
        token = strstr(token, "_");
    }
    return snake_case;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}