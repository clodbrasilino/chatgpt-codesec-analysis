#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValidParentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t capacity = 64;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t count = 0;
    bool valid = true;
    size_t i = 0;

    while (s[i] != '\0') {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            if (count >= capacity) {
                size_t new_capacity = capacity * 2;
                char *new_stack = (char *)realloc(stack, new_capacity * sizeof(char));
                if (new_stack == NULL) {
                    free(stack);
                    return false;
                }
                capacity = new_capacity;
                stack = new_stack;
            }
            stack[count++] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (count == 0) {
                valid = false;
                break;
            }
            char topChar = stack[--count];
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                valid = false;
                break;
            }
        }
        i++;
    }

    if (count != 0) {
        valid = false;
    }

    free(stack);
    return valid;
}

int main(void) {
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";

    printf("%s: %s\n", test1, isValidParentheses(test1) ? "true" : "false");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "true" : "false");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "true" : "false");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "true" : "false");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "true" : "false");

    return 0;
}