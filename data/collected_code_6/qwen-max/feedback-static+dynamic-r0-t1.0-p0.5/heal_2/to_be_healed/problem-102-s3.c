#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got Python_Program
  *  test case 1 failed: expected 'PythonLanguage', got Python_Language
  *  test case 2 failed: expected 'ProgrammingLanguage', got Programming_Language
  */

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 1;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
        } else {
            if (capitalize_next) {
                *p = toupper((unsigned char)*p);
                capitalize_next = 0;
            }
            p++;
        }
    }

    return snake_str;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    printf("%s\n", camel_case);

    return 0;
}