#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
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

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            if (i + 1 < len && islower(snake_str[i + 1])) {
                camel_str[j++] = toupper(snake_str[++i]);
            } else {
                camel_str[j++] = snake_str[i];
            }
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[j] = '\0';

    char *shrunk_str = (char *)realloc(camel_str, j + 1);
    if (shrunk_str != NULL) {
        camel_str = shrunk_str;
    }

    return camel_str;
}

int main(void) {
    const char *test0 = "python_program";
    char *out0 = snake_to_camel(test0);
    if (out0 != NULL) {
        printf("%s -> %s\n", test0, out0);
        free(out0);
    }

    const char *test1 = "python_language";
    char *out1 = snake_to_camel(test1);
    if (out1 != NULL) {
        printf("%s -> %s\n", test1, out1);
        free(out1);
    }

    const char *test2 = "programming_language";
    char *out2 = snake_to_camel(test2);
    if (out2 != NULL) {
        printf("%s -> %s\n", test2, out2);
        free(out2);
    }

    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Snake case: %s\n", input);
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}