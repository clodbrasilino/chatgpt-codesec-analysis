#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected True, got <no output>
  */

bool is_valid_parentheses(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    int balance = 0;
    size_t len = strnlen(str, 1024);
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            balance++;
        } else if (str[i] == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }
    
    return balance == 0;
}

int main(void) {
    const char *test_cases[] = {
        "()",
        "(())",
        "()()",
        "(()",
        "())",
        "((()))",
        "(()())",
        "",
        "a(b)c",
        ")(",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("String: \"%s\" -> %s\n", 
               test_cases[i], 
               is_valid_parentheses(test_cases[i]) ? "Valid" : "Invalid");
    }
    
    return 0;
}