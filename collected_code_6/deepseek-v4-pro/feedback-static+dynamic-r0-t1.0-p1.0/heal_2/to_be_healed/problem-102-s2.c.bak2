#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
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

        if (capitalize_next) {
            camel_str[camel_index++] = toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            camel_str[camel_index++] = snake_str[i];
        }
    }

    camel_str[camel_index] = '\0';
    return camel_str;
}

int main(void) {
    const char *test1 = "python_program";
    const char *test2 = "python_language";
    const char *test3 = "programming_language";

    char *result = snake_to_camel(test1);
    if (result != NULL) {
        printf("%s", result);
        free(result);
    }

    result = snake_to_camel(test2);
    if (result != NULL) {
        printf("%s", result);
        free(result);
    }

    result = snake_to_camel(test3);
    if (result != NULL) {
        printf("%s", result);
        free(result);
    }

    return 0;
}