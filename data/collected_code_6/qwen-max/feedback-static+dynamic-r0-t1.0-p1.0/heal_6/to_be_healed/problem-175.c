#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValidParentheses(const char* s, size_t len) {
    if (len % 2 != 0) return false;

    int stack[len];
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else if (s[i] == ')') {
            if (top == -1) return false;
            --top;
        }
    }

    return top == -1;
}

int main() {
    const char* test1 = "()";
    const char* test2 = "(()())";
    const char* test3 = "(()";
    const char* test4 = "())(";

    /* Possible weaknesses found:
     *  Condition 'isValidParentheses(test1,sizeof(test1)-1)' is always false
     *  Condition 'isValidParentheses(test1,sizeof(test1)-1)' is always false [knownConditionTrueFalse]
     *  Calling function 'isValidParentheses' returns 0
     */
    printf("%s: %s\n", test1, isValidParentheses(test1, sizeof(test1) - 1) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     *  Condition 'isValidParentheses(test2,sizeof(test2)-1)' is always false
     *  Condition 'isValidParentheses(test2,sizeof(test2)-1)' is always false [knownConditionTrueFalse]
     *  Calling function 'isValidParentheses' returns 0
     */
    printf("%s: %s\n", test2, isValidParentheses(test2, sizeof(test2) - 1) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     *  Condition 'isValidParentheses(test3,sizeof(test3)-1)' is always false
     *  Condition 'isValidParentheses(test3,sizeof(test3)-1)' is always false [knownConditionTrueFalse]
     *  Calling function 'isValidParentheses' returns 0
     */
    printf("%s: %s\n", test3, isValidParentheses(test3, sizeof(test3) - 1) ? "Valid" : "Invalid");
    /* Possible weaknesses found:
     *  Calling function 'isValidParentheses' returns 0
     *  Condition 'isValidParentheses(test4,sizeof(test4)-1)' is always false
     *  Condition 'isValidParentheses(test4,sizeof(test4)-1)' is always false [knownConditionTrueFalse]
     */
    printf("%s: %s\n", test4, isValidParentheses(test4, sizeof(test4) - 1) ? "Valid" : "Invalid");

    return 0;
}