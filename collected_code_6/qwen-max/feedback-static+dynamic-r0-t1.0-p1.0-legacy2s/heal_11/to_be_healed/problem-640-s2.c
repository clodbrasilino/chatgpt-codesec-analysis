#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'alpha', got �u2
  *  test case 1 failed: expected 'string', got �u2
  *  test case 0 failed: expected 'python', got `u2
  */

char* remove_parenthesis(const char *s) {
    int len = strlen(s);
    char *result = (char*)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    int r_index = 0;
    int p_count = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            p_count++;
        } else if (s[i] == ')') {
            if (p_count > 0) {
                p_count--;
            }
        } else {
            result[r_index++] = s[i];
        }
    }

    result[r_index] = '\0';
    return result;
}

int main() {
    const char input[] = "python";
    char *output = remove_parenthesis(input);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    const char input2[] = "string";
    output = remove_parenthesis(input2);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    const char input3[] = "alpha";
    output = remove_parenthesis(input3);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    const char input4[] = "(test)";
    output = remove_parenthesis(input4);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    const char input5[] = "a(b)c(d)e";
    output = remove_parenthesis(input5);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    const char input6[] = "(()())";
    output = remove_parenthesis(input6);
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
    }

    return 0;
}