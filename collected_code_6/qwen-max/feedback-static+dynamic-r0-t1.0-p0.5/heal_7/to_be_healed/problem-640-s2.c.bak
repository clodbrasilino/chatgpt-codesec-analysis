#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got ��&
  *  test case 0 failed: expected 'python', got @�&
  *  test case 2 failed: expected 'alpha', got ��&
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
            if (depth > 0) depth--;
        } else if (depth == 0) {
            result[result_index++] = str[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char input1[] = "This is a (test string with (nested) parenthesis) and more text.";
    const char input2[] = "alpha(beta)";
    const char input3[] = "python(tutorial)";
    const char input4[] = "string(test)";

    char *output1 = remove_parenthesis_area(input1);
    char *output2 = remove_parenthesis_area(input2);
    char *output3 = remove_parenthesis_area(input3);
    char *output4 = remove_parenthesis_area(input4);

    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    if (output4 != NULL) {
        printf("%s\n", output4);
        free(output4);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}