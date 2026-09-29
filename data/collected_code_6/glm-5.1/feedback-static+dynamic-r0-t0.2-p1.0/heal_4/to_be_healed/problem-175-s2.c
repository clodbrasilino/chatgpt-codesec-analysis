#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_parentheses(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 1;
    }

    size_t len = strnlen(str, SIZE_MAX);
    size_t capacity = len;
    char *stack = (char *)malloc(capacity);
    if (stack == NULL) {
        return 0;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        char current = str[i];
        if (current == '(' || current == '{' || current == '[') {
            if (top >= capacity) {
                free(stack);
                return 0;
            }
            stack[top++] = current;
        } else if (current == ')' || current == '}' || current == ']') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char matched_open = stack[--top];
            if ((current == ')' && matched_open != '(') ||
                (current == '}' && matched_open != '{') ||
                (current == ']' && matched_open != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == 0);
    free(stack);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    if (verify_parentheses(argv[1])) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }

    return 0;
}