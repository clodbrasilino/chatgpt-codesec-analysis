#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got Pythonlanguage
  *  test case 0 failed: expected 'PythonProgram', got Pythonprogram
  *  test case 2 failed: expected 'ProgrammingLanguage', got Programminglanguage
  */

char* snake_to_camel(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '_') {
            str[i] = toupper(str[i + 1]);
            memmove(&str[i], &str[i + 1], strlen(&str[i]));
            i--; // Adjust index after removing underscore
        } else if (i == 0 || (i > 0 && str[i-1] == '_')) {
            str[i] = toupper(str[i]);
        }
    }
    return str;
}

int main() {
    char input[] = "example_snake_case_string";
    char *result = snake_to_camel(input);
    printf("%s\n", result);
    return 0;
}