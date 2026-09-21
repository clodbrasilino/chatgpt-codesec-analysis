#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got <no output>
  *  test case 2 failed: expected 'alpha', got <no output>
  *  test case 1 failed: expected 'string', got <no output>
  */

char* remove_parenthesis(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    char *write_pos = result;
    int parenthesis_level = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            parenthesis_level++;
        } else if (str[i] == ')') {
            parenthesis_level--;
        } else if (parenthesis_level == 0) {
            *write_pos++ = str[i];
        }
    }

    *write_pos = '\0';
    return result;
}

int main() {
    const char input1[] = "(python)";
    const char input2[] = "a(lpha)";
    const char input3[] = "s(t(ring))";

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