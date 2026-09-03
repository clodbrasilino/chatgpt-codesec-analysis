#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got programminglanguage
  *  test case 1 failed: expected 'PythonLanguage', got pythonlanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonprogram
  */

char* snake_to_camel(char *snake_case) {
    char *original = snake_case;
    while (*snake_case) {
        if (*snake_case == '_') {
            *snake_case = toupper(*(snake_case + 1));
            memmove(snake_case, snake_case + 1, strlen(snake_case));
        } else {
            snake_case++;
        }
    }
    return original;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    printf("Original: %s\n", snake_case);
    printf("CamelCase: %s\n", snake_to_camel(snake_case));
    return 0;
}