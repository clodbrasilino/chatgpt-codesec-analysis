#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 4096

bool is_valid_parentheses(const char *input)
{
    size_t length;
    char *stack;
    size_t top = 0;
    size_t i;
    bool result = true;

    if (input == NULL) {
        return false;
    }

    length = strnlen(input, MAX_INPUT_LENGTH);
    if (length == MAX_INPUT_LENGTH && input[MAX_INPUT_LENGTH - 1] != '\0') {
        return false;
    }

    if (length == 0) {
        return true;
    }

    stack = malloc(length);
    if (stack == NULL) {
        return false;
    }

    for (i = 0; i < length; i++) {
        char c = input[i];

        if (c == '(' || c == '[' || c == '{') {
            if (top >= length) {
                result = false;
                break;
            }
            stack[top] = c;
            top++;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top == 0) {
                result = false;
                break;
            }
            top--;
            if ((c == ')' && stack[top] != '(') ||
                (c == ']' && stack[top] != '[') ||
                (c == '}' && stack[top] != '{')) {
                result = false;
                break;
            }
        } else {
            result = false;
            break;
        }
    }

    if (result && top != 0) {
        result = false;
    }

    free(stack);
    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LENGTH];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[sizeof(buffer) - 1] = '\0';

        size_t len = strnlen(buffer, sizeof(buffer));

        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }

        if (is_valid_parentheses(buffer)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    return EXIT_SUCCESS;
}