#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  */

char *snake_to_camel(const char *snake) {
    if (snake == NULL) return NULL;

    size_t len = strlen(snake);
    if (len == 0) {
        char *camel = malloc(1);
        if (camel == NULL) return NULL;
        camel[0] = '\0';
        return camel;
    }

    char *camel = malloc(len + 1);
    if (camel == NULL) return NULL;

    int capitalize_next = 0;
    size_t j = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                camel[j++] = toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
        }
    }
    camel[j] = '\0';

    char *shrunk = realloc(camel, j + 1);
    if (shrunk != NULL) {
        camel = shrunk;
    }

    return camel;
}

int main(void) {
    char *result;

    result = snake_to_camel("python_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("programming_language");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("python_program");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("_leading_underscore");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("trailing_underscore_");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("multiple___underscores");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel("alreadycamel");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}