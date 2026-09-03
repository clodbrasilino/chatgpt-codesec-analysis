#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got �ԉ
  *  test case 2 failed: expected 'alpha', got �ԉ
  *  test case 0 failed: expected 'python', got @ԉ
  */

char* remove_parenthesis_area(const char *input) {
    int input_len = strlen(input);
    int new_len = 0;
    int depth = 0;

    for (int i = 0; i < input_len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            new_len++;
        }
    }

    if (new_len == 0) {
        return strdup("");
    }

    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < input_len; ++i) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j++] = input[i];
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    const char *input1 = "This is a (test string with (nested) parentheses)";
    const char *input2 = "alpha(beta)gamma(delta)epsilon";
    const char *input3 = "python";

    char *output1 = remove_parenthesis_area(input1);
    if (output1 != NULL) {
        printf("%s\n", output1);
        free(output1);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    char *output2 = remove_parenthesis_area(input2);
    if (output2 != NULL) {
        printf("%s\n", output2);
        free(output2);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    char *output3 = remove_parenthesis_area(input3);
    if (output3 != NULL) {
        printf("%s\n", output3);
        free(output3);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
    }

    return 0;
}