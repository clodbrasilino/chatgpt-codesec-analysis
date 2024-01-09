#include <stdbool.h>

bool isValidParentheses(char* s) {
    int count = 0;
    
    for (int i = 0; s[i] != '\0'; i++) {
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