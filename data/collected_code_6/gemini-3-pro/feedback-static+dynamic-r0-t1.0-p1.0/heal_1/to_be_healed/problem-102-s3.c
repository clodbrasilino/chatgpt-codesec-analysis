#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  */

char* snake_to_camel(const char* snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(snake_str);
    char* camel_str = (char*)malloc(len + 1);
    if (camel_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    int capitalize_next = 0;

    for (size_t i = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next && j > 0) {
                camel_str[j++] = toupper((unsigned char)snake_str[i]);
                capitalize_next = 0;
            } else {
                camel_str[j++] = snake_str[i];
                capitalize_next = 0;
            }
        }
    }
    camel_str[j] = '\0';

    return camel_str;
}

int main(void) {
    const char* snake1 = "hello_world";
    const char* snake2 = "convert_this_snake_case";
    const char* snake3 = "_leading_underscore";
    
    char* camel1 = snake_to_camel(snake1);
    char* camel2 = snake_to_camel(snake2);
    char* camel3 = snake_to_camel(snake3);

    if (camel1 != NULL) {
        printf("%s -> %s\n", snake1, camel1);
        free(camel1);
    }
    
    if (camel2 != NULL) {
        printf("%s -> %s\n", snake2, camel2);
        free(camel2);
    }

    if (camel3 != NULL) {
        printf("%s -> %s\n", snake3, camel3);
        free(camel3);
    }

    return 0;
}