#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool isValidParentheses(const char* s) {
    int count = 0;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(s);
    
    for (unsigned int i = 0; i < length; i++) {
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
    printf("%s is %s\n", test, isValidParentheses(test) ? "valid" : "invalid");
    return 0;
}