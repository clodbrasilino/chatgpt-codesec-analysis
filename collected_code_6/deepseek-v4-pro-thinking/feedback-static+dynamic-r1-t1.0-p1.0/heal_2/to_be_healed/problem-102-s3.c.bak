#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  */

char *snake_to_camel(char *str) {
    size_t read, write;
    size_t length;
    int capitalize_next;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    length = strlen(str);
    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    write = 0;
    capitalize_next = 0;

    for (read = 0; str[read] != '\0'; ++read) {
        unsigned char c = (unsigned char)str[read];

        if (c == '_') {
            if (write > 0) {
                capitalize_next = 1;
            }
        } else if (write == 0) {
            result[write++] = (char)c;
        } else if (capitalize_next) {
            result[write++] = (char)toupper(c);
            capitalize_next = 0;
        } else {
            result[write++] = (char)c;
        }
    }

    result[write] = '\0';
    return result;
}

int main(void) {
    char test1[] = "Python_Program";
    char test2[] = "Python_Language";
    char test3[] = "Programming_Language";
    char *result;

    result = snake_to_camel(test1);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test2);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    result = snake_to_camel(test3);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    return 0;
}