#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char* snake_to_camel(const char *snake_str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (i < len) {
                result[j++] = toupper(snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char snake_case_str[] = "python_program";
    char *camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). Risk is low because the source is a constant string. (risk 1, buffer)
     */
    strncpy(snake_case_str, "program_language", 15);
    snake_case_str[14] = '\0';

    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    snprintf(snake_case_str, sizeof(snake_case_str), "python_language");
    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    return 0;
}