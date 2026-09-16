#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char* snake_to_camel(char *snake_str) {
    char *result = (char *)malloc(strlen(snake_str) + 1);
    if (result == NULL) {
        return NULL;
    }
    int i, j = 0;
    for (i = 0; snake_str[i]; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (snake_str[i]) {
                result[j++] = toupper(snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char snake_case_str[] = "python_program";
    char *camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    strncpy(snake_case_str, "program_language", sizeof(snake_case_str));
    snake_case_str[sizeof(snake_case_str) - 1] = '\0';

    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    snprintf(snake_case_str, sizeof(snake_case_str), "python_language");
    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);
    free(camel_case_str);

    return 0;
}