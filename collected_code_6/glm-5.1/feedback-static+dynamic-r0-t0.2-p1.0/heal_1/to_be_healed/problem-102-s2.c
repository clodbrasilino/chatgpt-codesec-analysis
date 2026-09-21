#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            if (i + 1 < len && islower((unsigned char)snake_str[i + 1])) {
                camel_str[j++] = (char)toupper((unsigned char)snake_str[i + 1]);
                i++;
            } else {
                camel_str[j++] = snake_str[i];
            }
        } else {
            camel_str[j++] = snake_str[i];
        }
    }

    camel_str[j] = '\0';
    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);

    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", output);
    free(output);
    output = NULL;

    return 0;
}