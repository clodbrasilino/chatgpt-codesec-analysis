#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  */

char* remove_parenthesis(char *str) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    char *write_pos = result;
    int parenthesis_level = 0;

    for (char *read_pos = str; *read_pos; read_pos++) {
        if (*read_pos == '(') {
            parenthesis_level++;
        } else if (*read_pos == ')') {
            if (parenthesis_level > 0) {
                parenthesis_level--;
            }
        } else if (parenthesis_level == 0) {
            *write_pos++ = *read_pos;
        }
    }

    *write_pos = '\0';
    return result;
}

int main() {
    char input1[] = "Example (with (nested) parenthesis) string.";
    char input2[] = "python (is a) programming language";
    char input3[] = "alpha(beta(gamma)) delta";

    char *output1 = remove_parenthesis(input1);
    char *output2 = remove_parenthesis(input2);
    char *output3 = remove_parenthesis(input3);

    printf("%s\n", output1 ? output1 : "");
    printf("%s\n", output2 ? output2 : "");
    printf("%s\n", output3 ? output3 : "");

    free(output1);
    free(output2);
    free(output3);
    return 0;
}