#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_balanced(const char *expression) {
    if (expression == NULL) {
        return 0;
    }

    size_t len = 0;
    while (expression[len] != '\0') {
        len++;
    }

    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;

    for (size_t i = 0; i < len; i++) {
        char ch = expression[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1) {
                free(stack);
                return 0;
            }
            char matched_open = stack[top--];
            if ((ch == ')' && matched_open != '(') ||
                (ch == '}' && matched_open != '{') ||
                (ch == ']' && matched_open != '[')) {
                free(stack);
                return 0;
            }
        }
    }

    int result = (top == -1) ? 1 : 0;
    free(stack);
    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <expression>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (is_balanced(argv[1])) {
        printf("Balanced\n");
    } else {
        printf("Not Balanced\n");
    }

    return EXIT_SUCCESS;
}