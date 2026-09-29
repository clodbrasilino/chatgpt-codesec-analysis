#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int verify_parentheses(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (len < SIZE_MAX && str[len] != '\0') {
        len++;
    }
    if (len == SIZE_MAX) {
        return 0;
    }

    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    size_t top = 0;
    for (size_t i = 0; i < len; i++) {
        char c = str[i];
        if (c == '(' || c == '{' || c == '[') {
            if (top < len) {
                stack[top++] = c;
            }
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == 0) {
                free(stack);
                return 0;
            }
            char last_open = stack[--top];
            if ((c == ')' && last_open != '(') ||
                (c == '}' && last_open != '{') ||
                (c == ']' && last_open != '[')) {
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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
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