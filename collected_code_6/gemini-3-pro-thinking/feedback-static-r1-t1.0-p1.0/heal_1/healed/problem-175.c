#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STR_LEN 1048576

bool is_valid_parentheses(const char *s) {
    if (s == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < MAX_STR_LEN && s[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return true;
    }

    if (len % 2 != 0) {
        return false;
    }

    char *stack = (char *)malloc(len * sizeof(char));
    if (stack == NULL) {
        return false;
    }

    size_t top = 0;
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[top++] = s[i];
        } else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if (top == 0) {
                free(stack);
                return false;
            }
            
            char open_bracket = stack[--top];
            if ((s[i] == ')' && open_bracket != '(') ||
                (s[i] == ']' && open_bracket != '[') ||
                (s[i] == '}' && open_bracket != '{')) {
                free(stack);
                return false;
            }
        }
    }

    bool is_valid = (top == 0);
    free(stack);
    
    return is_valid;
}

int main(void) {
    const char *test_strings[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        bool result = is_valid_parentheses(test_strings[i]);
        if (result) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
    }

    return 0;
}