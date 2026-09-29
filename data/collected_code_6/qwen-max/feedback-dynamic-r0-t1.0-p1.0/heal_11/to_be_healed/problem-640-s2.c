#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got 
  *  test case 0 failed: expected 'python', got �a�
  *  test case 2 failed: expected 'alpha', got @b�
  */

char* remove_parenthesis(const char *str) {
    int len = strlen(str);
    int result_len = 0;
    int in_parenthesis = 0;
    for (const char *p = str; *p; p++) {
        if (*p == '(') {
            in_parenthesis = 1;
        } else if (*p == ')') {
            in_parenthesis = 0;
        } else if (!in_parenthesis) {
            result_len++;
        }
    }

    char *result = (char*)malloc(result_len + 1);
    if (result == NULL) return NULL;

    char *write_pos = result;
    in_parenthesis = 0;
    for (const char *read_pos = str; *read_pos; read_pos++) {
        if (*read_pos == '(') {
            in_parenthesis = 1;
        } else if (*read_pos == ')') {
            in_parenthesis = 0;
        } else if (!in_parenthesis) {
            *write_pos++ = *read_pos;
        }
    }

    *write_pos = '\0';
    return result;
}

int main() {
    const char input1[] = "python(should-remove)";
    const char input2[] = "a(b(c)d)";
    const char input3[] = "string(with(parenthesis))";

    char *output1 = remove_parenthesis(input1);
    char *output2 = remove_parenthesis(input2);
    char *output3 = remove_parenthesis(input3);

    if (output1) {
        printf("%s\n", output1);
        free(output1);
    }

    if (output2) {
        printf("%s\n", output2);
        free(output2);
    }

    if (output3) {
        printf("%s\n", output3);
        free(output3);
    }

    return 0;
}