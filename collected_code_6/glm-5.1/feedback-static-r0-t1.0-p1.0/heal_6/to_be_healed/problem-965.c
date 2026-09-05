#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = strlen(camel_str);
    char *snake_str = malloc(len > 0 ? len * 2 + 1 : 1);
    if (snake_str == NULL) {
        return NULL;
    }

    if (len == 0) {
        snake_str[0] = '\0';
        return snake_str;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[j++] = '_';
            }
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }

    snake_str[j] = '\0';

    char *shrunk = realloc(snake_str, j + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

int main(void) {
    const char *inputs[] = {
        "camelCase",
        "CamelCase",
        "thisIsATest",
        "single",
        "T",
        "",
        NULL
    };

    for (size_t i = 0; inputs[i] != NULL; i++) {
        char *result = camel_to_snake(inputs[i]);
        if (result != NULL) {
            printf("\"%s\" -> \"%s\"\n", inputs[i], result);
            free(result);
        } else {
            printf("\"%s\" -> (conversion failed)\n", inputs[i]);
        }
    }

    /* Possible weaknesses found:
     *  Assignment 'null_test=camel_to_snake(NULL)', assigned value is 0
     *  Calling function 'camel_to_snake' returns 0
     */
    char *null_test = camel_to_snake(NULL);
    /* Possible weaknesses found:
     *  Variable 'ptr' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'ptr=(void*)null_test', assigned value is 0
     */
    void *ptr = (void *)null_test;
    /* Possible weaknesses found:
     *  Condition 'ptr==NULL' is always true
     *  Condition 'ptr==NULL' is always true [knownConditionTrueFalse]
     */
    if (ptr == NULL) {
        printf("NULL input handled correctly.\n");
    } else {
        free(null_test);
    }

    return 0;
}