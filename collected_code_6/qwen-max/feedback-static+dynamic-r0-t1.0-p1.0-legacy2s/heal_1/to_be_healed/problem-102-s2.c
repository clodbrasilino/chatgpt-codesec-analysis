#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  */

char* snake_to_camel(char *snake_str) {
    int i, capitalize_next = 0;
    for (i = 0; snake_str[i] != '\0'; ++i) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            snake_str[i] = toupper(snake_str[i]);
            capitalize_next = 0;
        }
    }
    char *src = snake_str;
    char *dst = src;
    while (*src) {
        if (*src != '_') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
    return snake_str;
}

int main() {
    char snake_case[] = "this_is_a_test_string";
    char *camel_case = snake_to_camel(snake_case);
    printf("%s\n", camel_case);
    return 0;
}