#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got ProgrammingLlanguage
  *  test case 0 failed: expected 'PythonProgram', got PythonPprogram
  *  test case 1 failed: expected 'PythonLanguage', got PythonLlanguage
  */

char *snake_to_camel(const char *snake) {
    size_t len;
    size_t i;
    size_t j;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    len = strlen(snake);
    camel = (char *)malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;

    while (i < len && snake[i] == '_') {
        i++;
    }

    if (i < len) {
        if ((unsigned char)snake[i] >= 'a' && (unsigned char)snake[i] <= 'z') {
            camel[j++] = snake[i] - 32;
        } else {
            camel[j++] = snake[i];
        }
        i++;
    }

    while (i < len) {
        if (snake[i] == '_') {
            i++;
            while (i < len && snake[i] == '_') {
                i++;
            }
            if (i < len) {
                if ((unsigned char)snake[i] >= 'a' && (unsigned char)snake[i] <= 'z') {
                    camel[j++] = snake[i] - 32;
                } else {
                    camel[j++] = snake[i];
                }
            }
        } else {
            camel[j++] = snake[i];
            i++;
        }
    }

    camel[j] = '\0';

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

    result = snake_to_camel("hello_world_example");
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}