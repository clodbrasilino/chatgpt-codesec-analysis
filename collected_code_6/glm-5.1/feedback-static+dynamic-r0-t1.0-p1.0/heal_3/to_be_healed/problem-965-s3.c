#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t new_len = len + 1;
    for (size_t i = 1; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            new_len++;
        }
    }

    char *snake_str = malloc(new_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i])) {
            snake_str[j++] = '_';
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        }
    }
    snake_str[j] = '\0';

    return snake_str;
}

int main(void) {
    const char *inputs[] = {
        "pythonProgram",
        "pythonLanguage",
        "programmingLanguage",
        "CamelCase",
        "snake_case",
        "already_snake_case",
        "singleword",
        "",
        "HTTPRequest",
        "XMLParser"
    };

    size_t count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < count; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        } else {
            printf("Allocation failed for: %s\n", inputs[i]);
        }
    }

    /* Possible weaknesses found:
     *  Calling function 'camel_to_snake' returns 0
     *  Assignment 'null_test=camel_to_snake(NULL)', assigned value is 0
     */
    char *null_test = camel_to_snake(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_test==NULL' is always true
     */
    if (null_test == NULL) {
        printf("Null input handled correctly.\n");
    } else {
        free(null_test);
    }

    return 0;
}