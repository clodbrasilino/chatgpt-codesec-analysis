#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got `cs
  *  test case 2 failed: expected 'alpha', got �cs
  *  test case 0 failed: expected 'python', got  cs
  */

char* remove_parenthesis_area(const char *str) {
    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) return NULL;
    int result_index = 0;
    int depth = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            depth--;
        } else if (depth == 0) {
            result[result_index++] = str[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char input[] = "This is a (test string with (nested) parenthesis) and more text.";
    char *output = remove_parenthesis_area(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }
    return 0;
}