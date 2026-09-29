#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got pythonLanguage
  *  test case 2 failed: expected 'ProgrammingLanguage', got programmingLanguage
  *  test case 0 failed: expected 'PythonProgram', got pythonProgram
  */

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 0;
    int index = 0;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next && isalpha(*p)) {
            snake_str[index] = toupper(*p);
            capitalize_next = 0;
        } else {
            snake_str[index] = *p;
        }
        index++;
        p++;
    }
    snake_str[index] = '\0';
    return snake_str;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    printf("%s\n", camel_case);

    return 0;
}