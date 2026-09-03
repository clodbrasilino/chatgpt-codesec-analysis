#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  */

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = strlen(snake);
    char *camel = (char *)malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int capitalize_next = 0;

    while (snake[i] != '\0') {
        if (snake[i] == '_') {
            capitalize_next = 1;
            i++;
            continue;
        }

        if (capitalize_next && j == 0) {
            camel[j++] = snake[i];
            capitalize_next = 0;
        } else if (capitalize_next) {
            camel[j++] = (char)toupper((unsigned char)snake[i]);
            capitalize_next = 0;
        } else {
            camel[j++] = snake[i];
        }
        i++;
    }

    camel[j] = '\0';
    return camel;
}

int main(void) {
    const char *test1 = "hello_world";
    const char *test2 = "snake_case_string";
    const char *test3 = "alreadyCamel";
    const char *test4 = "multiple__underscores";
    const char *test5 = "_leading_underscore";
    const char *test6 = "trailing_underscore_";
    const char *test7 = "";
    const char *test8 = "python_program";
    const char *test9 = "python_language";
    const char *test10 = "programming_language";

    char *result;

    result = snake_to_camel(test1);
    if (result != NULL) {
        printf("%s -> %s\n", test1, result);
        free(result);
    }

    result = snake_to_camel(test2);
    if (result != NULL) {
        printf("%s -> %s\n", test2, result);
        free(result);
    }

    result = snake_to_camel(test3);
    if (result != NULL) {
        printf("%s -> %s\n", test3, result);
        free(result);
    }

    result = snake_to_camel(test4);
    if (result != NULL) {
        printf("%s -> %s\n", test4, result);
        free(result);
    }

    result = snake_to_camel(test5);
    if (result != NULL) {
        printf("%s -> %s\n", test5, result);
        free(result);
    }

    result = snake_to_camel(test6);
    if (result != NULL) {
        printf("%s -> %s\n", test6, result);
        free(result);
    }

    result = snake_to_camel(test7);
    if (result != NULL) {
        printf("\"%s\" -> \"%s\"\n", test7, result);
        free(result);
    }

    result = snake_to_camel(test8);
    if (result != NULL) {
        printf("%s -> %s\n", test8, result);
        free(result);
    }

    result = snake_to_camel(test9);
    if (result != NULL) {
        printf("%s -> %s\n", test9, result);
        free(result);
    }

    result = snake_to_camel(test10);
    if (result != NULL) {
        printf("%s -> %s\n", test10, result);
        free(result);
    }

    return 0;
}