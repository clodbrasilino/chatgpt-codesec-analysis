#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got �AD
  *  test case 1 failed: expected 'string', got �AD
  *  test case 2 failed: expected 'alpha', got 
  */

char* remove_parenthesis(const char *str) {
    int len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;

    char *write_pos = result;
    int parenthesis_level = 0;

    for (const char *read_pos = str; *read_pos; read_pos++) {
        if (*read_pos == '(') {
            parenthesis_level++;
        } else if (*read_pos == ')' && parenthesis_level > 0) {
            parenthesis_level--;
        } else if (*read_pos != ')' || parenthesis_level == 0) {
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
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (output2) {
        printf("%s\n", output2);
        free(output2);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    if (output3) {
        printf("%s\n", output3);
        free(output3);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}