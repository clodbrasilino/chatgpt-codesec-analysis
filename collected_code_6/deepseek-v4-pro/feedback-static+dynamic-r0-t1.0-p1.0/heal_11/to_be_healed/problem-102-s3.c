#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  */

char *snake_to_camel(const char *snake) {
    if (snake == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (snake[len] != '\0') {
        len++;
    }

    size_t new_len = 0;
    int has_chars = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] != '_') {
            new_len++;
            has_chars = 1;
        }
    }

    if (!has_chars) {
        char *camel = (char *)malloc(1);
        if (camel != NULL) {
            camel[0] = '\0';
        }
        return camel;
    }

    char *camel = (char *)malloc(new_len + 1);
    if (camel == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 0;
    int first_char = 1;

    for (size_t i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (first_char) {
                camel[j++] = snake[i];
                first_char = 0;
                capitalize_next = 0;
            } else if (capitalize_next) {
                camel[j++] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j++] = snake[i];
            }
        }
    }

    camel[j] = '\0';
    return camel;
}

int main(void) {
    const char *test1 = "snake_case_string";
    const char *test2 = "_leading_underscore";
    const char *test3 = "trailing_underscore_";
    const char *test4 = "multiple__underscores";
    const char *test5 = "alreadyCamel";
    const char *test6 = "";
    const char *test7 = "a";
    const char *test8 = "a_b_c_d_e_f";
    const char *test9 = "python_language";
    const char *test10 = "programming_language";
    const char *test11 = "python_program";

    char *result = NULL;

    result = snake_to_camel(test1);
    printf("%s -> %s\n", test1, result ? result : "");
    free(result);

    result = snake_to_camel(test2);
    printf("%s -> %s\n", test2, result ? result : "");
    free(result);

    result = snake_to_camel(test3);
    printf("%s -> %s\n", test3, result ? result : "");
    free(result);

    result = snake_to_camel(test4);
    printf("%s -> %s\n", test4, result ? result : "");
    free(result);

    result = snake_to_camel(test5);
    printf("%s -> %s\n", test5, result ? result : "");
    free(result);

    result = snake_to_camel(test6);
    printf("\"%s\" -> \"%s\"\n", test6, result ? result : "");
    free(result);

    result = snake_to_camel(test7);
    printf("%s -> %s\n", test7, result ? result : "");
    free(result);

    result = snake_to_camel(test8);
    printf("%s -> %s\n", test8, result ? result : "");
    free(result);

    result = snake_to_camel(test9);
    printf("%s -> %s\n", test9, result ? result : "");
    free(result);

    result = snake_to_camel(test10);
    printf("%s -> %s\n", test10, result ? result : "");
    free(result);

    result = snake_to_camel(test11);
    printf("%s -> %s\n", test11, result ? result : "");
    free(result);

    /* Possible weaknesses found:
     *  Assignment 'result=snake_to_camel(NULL)', assigned value is 0
     *  Calling function 'snake_to_camel' returns 0
     */
    result = snake_to_camel(NULL);
    /* Possible weaknesses found:
     *  Condition 'result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'result==NULL' is always true
     */
    if (result == NULL) {
        printf("NULL -> NULL\n");
    }

    return 0;
}