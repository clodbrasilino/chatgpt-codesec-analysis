#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got ���
  *  test case 2 failed: expected 'alpha', got ���
  *  test case 0 failed: expected 'python', got `��
  */

char* remove_parenthesis(char *str) {
    char *result = (char*)malloc(strlen(str) + 1);
    char *write_pos = result;
    int parenthesis_level = 0;

    for (char *read_pos = str; *read_pos; read_pos++) {
        if (*read_pos == '(') {
            parenthesis_level++;
        } else if (*read_pos == ')') {
            parenthesis_level--;
        } else if (parenthesis_level == 0) {
            *write_pos++ = *read_pos;
        }
    }

    *write_pos = '\0';
    return result;
}

int main() {
    char input[] = "Example (with (nested) parenthesis) string.";
    char *output = remove_parenthesis(input);

    printf("%s\n", output);

    free(output);
    return 0;
}