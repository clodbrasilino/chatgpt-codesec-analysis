#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got _programming_language
  *  test case 0 failed: expected 'python_program', got _python_program
  */

char *camel_to_snake(const char *camel) {
    if (camel == NULL) {
        return NULL;
    }

    size_t len = strlen(camel);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t upper_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            upper_count++;
        }
    }

    char *snake = malloc(len + upper_count + 1);
    if (snake == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel[i])) {
            snake[j++] = '_';
            snake[j++] = tolower((unsigned char)camel[i]);
        } else {
            snake[j++] = camel[i];
        }
    }
    snake[j] = '\0';

    return snake;
}

int main(void) {
    const char *inputs[] = {
        "camelCaseString",
        "thisIsATest",
        "C",
        "already_snake",
        "simple",
        "",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("%s -> %s\n", inputs[i], result);
            free(result);
        } else {
            printf("Failed to convert string.\n");
        }
    }

    /* Possible weaknesses found:
     *  Variable 'null_test' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'camel_to_snake' returns 0
     *  Assignment 'null_test=camel_to_snake(NULL)', assigned value is 0
     */
    char *null_test = camel_to_snake(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_test==NULL' is always true
     *  Condition 'null_test==NULL' is always true [knownConditionTrueFalse]
     */
    if (null_test == NULL) {
        printf("Successfully handled NULL input.\n");
    }

    return 0;
}