#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char* snake_to_camel(char *snake_str) {
    int len = strlen(snake_str);
    char *camel_str = snake_str;
    int capitalize_next = 0;

    for (int i = 0, j = 0; i < len; i++) {
        if (snake_str[i] == '_') {
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next) {
            camel_str[j++] = toupper((unsigned char)snake_str[i]);
            capitalize_next = 0;
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[len + 1] = '\0';
    return camel_str;
}

int main() {
    char test_case_0[] = "python_program";
    char test_case_1[] = "python_language";
    char test_case_2[] = "programming_language";

    printf("%s\n", snake_to_camel(test_case_0));
    printf("%s\n", snake_to_camel(test_case_1));
    printf("%s\n", snake_to_camel(test_case_2));

    return 0;
}