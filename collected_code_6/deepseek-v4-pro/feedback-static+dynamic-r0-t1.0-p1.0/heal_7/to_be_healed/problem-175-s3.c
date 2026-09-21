#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

bool isValidParentheses(const char *s) {
    if (s == NULL) return false;
    
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
        if (len > 1048576) return false;
    }
    
    if (len == 0) return true;
    
    char *stack = malloc(len + 1);
    if (stack == NULL) return false;
    
    int top = -1;
    
    for (size_t i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char opening = stack[top--];
            if ((c == ')' && opening != '(') ||
                (c == ']' && opening != '[') ||
                (c == '}' && opening != '{')) {
                free(stack);
                return false;
            }
        }
    }
    
    bool result = (top == -1);
    free(stack);
    return result;
}

int main(void) {
    char *input = NULL;
    size_t buffer_size = 0;
    
    printf("Enter a string of parentheses: ");
    ssize_t read_len = getline(&input, &buffer_size, stdin);
    if (read_len == -1) {
        free(input);
        return 1;
    }
    
    if (read_len > 0 && input[read_len - 1] == '\n') {
        input[read_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'read_len' is assigned a value that is never used. [unreadVariable]
         */
        read_len--;
    }
    
    if (isValidParentheses(input)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    free(input);
    return 0;
}