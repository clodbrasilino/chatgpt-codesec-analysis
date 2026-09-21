#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char *camel_to_snake(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    size_t max_size = len * 2 + 1;
    char *result = (char *)malloc(max_size);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int last_was_underscore = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];

        if (c == '_') {
            result[j++] = '_';
            last_was_underscore = 1;
        } else if (isupper(c)) {
            if (j > 0 && !last_was_underscore && result[j - 1] != '_') {
                result[j++] = '_';
            }
            result[j++] = tolower(c);
            last_was_underscore = 0;
        } else {
            result[j++] = c;
            last_was_underscore = 0;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *tests[] = {
        "camelCase",
        "PascalCase",
        "already_snake",
        "ABC",
        "aBc",
        "",
        "helloWorldExample",
        "CamelCaseTest123",
        NULL
    };

    for (int i = 0; tests[i] != NULL; i++) {
        char *converted = camel_to_snake(tests[i]);
        if (converted != NULL) {
            printf("%s -> %s\n", tests[i], converted);
            free(converted);
        } else {
            printf("%s -> (null)\n", tests[i]);
        }
    }

    return 0;
}