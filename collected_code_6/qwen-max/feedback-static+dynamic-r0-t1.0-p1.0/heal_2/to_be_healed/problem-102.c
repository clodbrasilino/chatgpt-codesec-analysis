#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char* snake_to_camel(char *str) {
    int i, len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    for (i = 0; *str; str++) {
        if (*str == '_') {
            str++;
            if (*str) {
                result[i++] = toupper(*str);
            }
        } else {
            result[i++] = *str;
        }
    }
    result[i] = '\0';
    return result;
}

int main() {
    char input[] = "this_is_snake_case";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}