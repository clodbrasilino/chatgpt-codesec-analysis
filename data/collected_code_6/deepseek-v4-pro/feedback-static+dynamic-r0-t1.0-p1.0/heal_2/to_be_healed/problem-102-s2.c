#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    size_t camel_len = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'prev_underscore' can be reduced. [variableScope]
     */
    int prev_underscore = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            /* Possible weaknesses found:
             *  Value stored to 'prev_underscore' is never read [deadcode.DeadStores]
             */
            prev_underscore = 1;
        } else {
            camel_len++;
            /* Possible weaknesses found:
             *  Value stored to 'prev_underscore' is never read [deadcode.DeadStores]
             */
            prev_underscore = 0;
        }
    }

    char *camel_str = (char *)malloc(camel_len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t camel_index = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next && camel_index > 0) {
            camel_str[camel_index++] = toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            if (camel_index == 0) {
                camel_str[camel_index++] = tolower((unsigned char)snake_str[i]);
            } else {
                camel_str[camel_index++] = snake_str[i];
            }
            capitalize_next = 0;
        }
    }

    camel_str[camel_index] = '\0';
    return camel_str;
}

int main(void) {
    const char *test1 = "python_program";
    const char *test2 = "python_language";
    const char *test3 = "programming_language";
    const char *test4 = "snake_case_string";
    const char *test5 = "alreadyCamelCase";
    const char *test6 = "multiple__underscores";
    const char *test7 = "trailing_underscore_";
    const char *test8 = "_leading_underscore";
    const char *test9 = "";

    char *result = snake_to_camel(test1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test2);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test3);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test4);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test5);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test6);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test7);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test8);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test9);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}