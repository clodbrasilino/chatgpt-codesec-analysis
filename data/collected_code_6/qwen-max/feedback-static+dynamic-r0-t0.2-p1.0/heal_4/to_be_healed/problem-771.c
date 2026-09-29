#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

bool isBalanced(const char *expression, size_t len) {
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *stack = (char *)malloc(len * sizeof(char));
    if (!stack) return false;
    int top = -1;

    for (size_t i = 0; i < len; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            if (top + 1 >= (int)len) {
                /* Possible weaknesses found:
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 *  include '<stdlib.h>' or provide a declaration of 'free'
                 */
                free(stack);
                return false;
            }
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) {
                free(stack);
                return false;
            }
            char last = stack[top--];
            if ((expression[i] == ')' && last != '(') ||
                (expression[i] == ']' && last != '[') ||
                (expression[i] == '}' && last != '{')) {
                free(stack);
                return false;
            }
        }
    }

    free(stack);
    return top == -1;
}

int main() {
    const char *expressions[] = {
        "([]{})",
        "([)]",
        "{[()]}",
        "{[(])}",
        "{{[[(())]]}}",
        "(()"
    };

    for (size_t i = 0; i < sizeof(expressions) / sizeof(expressions[0]); i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(expressions[i]);
        printf("%s: %s\n", expressions[i], isBalanced(expressions[i], len) ? "Balanced" : "Not Balanced");
    }

    return 0;
}