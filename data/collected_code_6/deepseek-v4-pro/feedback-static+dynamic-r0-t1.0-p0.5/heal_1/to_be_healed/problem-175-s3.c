#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

bool isValidParentheses(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s);
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *stack = (char *)malloc(len + 1);
    if (stack == NULL) {
        return false;
    }
    int top = -1;
    
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else if (c == ')' || c == '}' || c == ']') {
            if (top == -1) {
                /* Possible weaknesses found:
                 *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
                 *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
                 *  include '<stdlib.h>' or provide a declaration of 'free'
                 *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                free(stack);
                return false;
            }
            char open = stack[top--];
            /* Possible weaknesses found:
             * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
             */
            if ((c == ')' && open != '(') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (c == '}' && open != '{') ||
                /* Possible weaknesses found:
                 * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
                 */
                (c == ']' && open != '[')) {
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
    const char *test1 = "()";
    const char *test2 = "()[]{}";
    const char *test3 = "(]";
    const char *test4 = "([)]";
    const char *test5 = "{[]}";
    const char *test6 = "";
    const char *test7 = "(";
    const char *test8 = ")";
    
    printf("%s: %s\n", test1, isValidParentheses(test1) ? "valid" : "invalid");
    printf("%s: %s\n", test2, isValidParentheses(test2) ? "valid" : "invalid");
    printf("%s: %s\n", test3, isValidParentheses(test3) ? "valid" : "invalid");
    printf("%s: %s\n", test4, isValidParentheses(test4) ? "valid" : "invalid");
    printf("%s: %s\n", test5, isValidParentheses(test5) ? "valid" : "invalid");
    printf("%s: %s\n", test6, isValidParentheses(test6) ? "valid" : "invalid");
    printf("%s: %s\n", test7, isValidParentheses(test7) ? "valid" : "invalid");
    printf("%s: %s\n", test8, isValidParentheses(test8) ? "valid" : "invalid");
    
    return 0;
}