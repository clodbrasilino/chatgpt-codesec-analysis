#include <stdio.h>
#include <stdbool.h>

bool is_valid_parentheses(const char *s, size_t max_len) {
    int balance = 0;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<max_len' is not redundant
     */
    for (size_t i = 0; i < max_len; ++i) {
        /* Possible weaknesses found:
         *  Array 's[3]' accessed at index 6, which is out of bounds. [arrayIndexOutOfBounds]
         *  Array index out of bounds
         */
        if (s[i] == '(') {
            balance++;
        } else if (s[i] == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }
    return balance == 0;
}

int main() {
    const char *test1 = "()";
    const char *test2 = "(()())";
    const char *test3 = ")(";
    const char *test4 = "(()";

    /* Possible weaknesses found:
     *  Calling function 'is_valid_parentheses', 2nd argument 'sizeof(test1)-1' value is 7
     */
    printf("%s: %s\n", test1, is_valid_parentheses(test1, sizeof(test1) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test2, is_valid_parentheses(test2, sizeof(test2) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test3, is_valid_parentheses(test3, sizeof(test3) - 1) ? "Valid" : "Invalid");
    printf("%s: %s\n", test4, is_valid_parentheses(test4, sizeof(test4) - 1) ? "Valid" : "Invalid");

    return 0;
}