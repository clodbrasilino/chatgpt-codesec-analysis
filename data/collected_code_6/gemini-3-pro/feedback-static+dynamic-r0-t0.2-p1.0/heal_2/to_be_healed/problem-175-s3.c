#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t capacity = 32;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool is_valid = true;

    for (size_t i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            if (top >= capacity) {
                capacity *= 2;
                char *new_stack = (char *)realloc(stack, capacity * sizeof(char));
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                stack = new_stack;
            }
            stack[top++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                is_valid = false;
                break;
            }
            char top_char = stack[--top];
            if ((c == ')' && top_char != '(') ||
                (c == '}' && top_char != '{') ||
                (c == ']' && top_char != '[')) {
                is_valid = false;
                break;
            }
        } else {
            is_valid = false;
            break;
        }
    }

    if (top != 0) {
        is_valid = false;
    }

    free(stack);
    return is_valid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";

    printf("%s: %s\n", test1, is_valid_parentheses(test1) ? "true" : "false");
    printf("%s: %s\n", test2, is_valid_parentheses(test2) ? "true" : "false");
    printf("%s: %s\n", test3, is_valid_parentheses(test3) ? "true" : "false");
    printf("%s: %s\n", test4, is_valid_parentheses(test4) ? "true" : "false");
    printf("%s: %s\n", test5, is_valid_parentheses(test5) ? "true" : "false");

    /* Possible weaknesses found:
     *  Calling function 'is_valid_parentheses' returns 0
     *  Assignment 'null_result=is_valid_parentheses(NULL)', assigned value is 0
     */
    bool null_result = is_valid_parentheses(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_result' is always false
     *  Condition 'null_result' is always false [knownConditionTrueFalse]
     */
    printf("NULL: %s\n", null_result ? "true" : "false");

    return 0;
}