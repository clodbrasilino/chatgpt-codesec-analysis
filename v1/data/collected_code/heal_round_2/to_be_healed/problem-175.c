#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isValidParentheses(const char* s) {
    int count = 0;
    
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '(')
            count++;
        else if (s[i] == ')') {
            if (count == 0)
                return false;
            count--;
        }
    }
    
    return count == 0;
}

int main() {
    char* test = "(())";
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("%s is %s\n", test, isValidParentheses(test) ? "valid" : "invalid");
    return 0;
}