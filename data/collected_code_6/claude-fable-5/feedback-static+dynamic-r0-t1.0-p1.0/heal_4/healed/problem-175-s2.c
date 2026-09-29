#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LEN 4096

bool is_valid_parentheses(const char *s)
{
    size_t len;
    char *stack;
    size_t top = 0;
    size_t i;
    bool result = true;

    if (s == NULL) {
        return false;
    }

    len = strnlen(s, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && s[MAX_INPUT_LEN - 1] != '\0') {
        return false;
    }

    if (len == 0) {
        return true;
    }

    stack = malloc(len);
    if (stack == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
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
    char *buffer;

    buffer = malloc(MAX_INPUT_LEN);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, MAX_INPUT_LEN, stdin) != NULL) {
        size_t len = strnlen(buffer, MAX_INPUT_LEN);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if (printf("%s\n", is_valid_parentheses(buffer) ? "True" : "False") < 0) {
            free(buffer);
            return EXIT_FAILURE;
        }
        if (fflush(stdout) != 0) {
            free(buffer);
            return EXIT_FAILURE;
        }
        free(buffer);
        return EXIT_SUCCESS;
    }

    free(buffer);

    const char *tests[] = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "",
        "((("
    };
    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        if (printf("%s\n", is_valid_parentheses(tests[i]) ? "True" : "False") < 0) {
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}