#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValid(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t capacity = 32;
    char *stack = (char *)malloc(capacity * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    bool valid = true;

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
                valid = false;
                break;
            }
            char open_bracket = stack[--top];
            if ((c == ')' && open_bracket != '(') ||
                (c == '}' && open_bracket != '{') ||
                (c == ']' && open_bracket != '[')) {
                valid = false;
                break;
            }
        }
    }

    if (top != 0) {
        valid = false;
    }

    free(stack);
    return valid;
}

int main(void) {
    const char *tests[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        NULL
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (tests[i] == NULL) {
            printf("NULL: %s\n", isValid(tests[i]) ? "true" : "false");
        } else {
            printf("%s: %s\n", tests[i], isValid(tests[i]) ? "true" : "false");
        }
    }

    return 0;
}