#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got 
  *  test case 0 failed: expected 'python', got ��
  *  test case 2 failed: expected 'alpha', got @�
  */

char* remove_parentheses(const char *input) {
    if (input == NULL) return NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) return NULL;

    int result_index = 0;
    int depth = 0;

    for (size_t i = 0; i < input_len; ++i) {
        /* Possible weaknesses found:
         *  Assuming condition 'input[i]=='('' is false
         */
        if (input[i] == '(') {
            depth++;
        /* Possible weaknesses found:
         *  Assuming condition 'input[i]==')'' is false
         */
        } else if (input[i] == ')') {
            depth--;
        /* Possible weaknesses found:
         *  Condition 'input[i]!='('' is always true
         *  Condition 'input[i]!='('' is always true [knownConditionTrueFalse]
         *  Condition 'input[i]!=')'' is always true [knownConditionTrueFalse]
         *  Condition 'input[i]!=')'' is always true
         */
        } else if (depth == 0 && input[i] != '(' && input[i] != ')') {
            result[result_index++] = input[i];
        }
    }

    result[result_index] = '\0';
    return result;
}

int main() {
    const char *test_cases[] = {"(python)", "string", "(alpha)"};
    const char *expected_outputs[] = {"", "string", ""};

    for (int i = 0; i < 3; ++i) {
        char *output = remove_parentheses(test_cases[i]);
        if (output != NULL) {
            printf("%s\n", output);
            free(output);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
        }
    }

    return 0;
}