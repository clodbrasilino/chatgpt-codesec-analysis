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
    char *p = snake_str;
    int capitalize_next = 1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        return NULL;
    }
    int index = 0;

    while (index < len + 1) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next && isalpha(*p)) {
            output[index] = toupper(*p);
            capitalize_next = 0;
        } else {
            output[index] = *p;
        }
        index++;
        p++;
    }
    output[len] = '\0';
    return output;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    if (camel_case != NULL) {
        printf("%s\n", camel_case);
        free(camel_case);
    }

    return 0;
}