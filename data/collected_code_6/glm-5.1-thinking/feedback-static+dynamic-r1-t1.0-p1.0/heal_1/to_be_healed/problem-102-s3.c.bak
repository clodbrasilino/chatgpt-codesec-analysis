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

    size_t len = strlen(snake_str);
    char *camel_str = malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel_str[j++] = (char)toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = (char)tolower((unsigned char)snake_str[i]);
            }
        }
    }

    camel_str[j] = '\0';
    return camel_str;
}

int main(void) {
    const char *inputs[] = {
        "hello_world",
        "snake_case_string",
        "alreadycamel",
        "_leading_underscore_",
        "trailing_underscore_",
        "multiple___underscores",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        char *result = snake_to_camel(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to allocate memory for: %s\n", inputs[i]);
        }
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=snake_to_camel(NULL)', assigned value is 0
     *  Variable 'null_test' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'snake_to_camel' returns 0
     */
    char *null_test = snake_to_camel(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}