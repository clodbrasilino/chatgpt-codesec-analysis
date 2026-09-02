#include <stdio.h>
#include <stdbool.h>

bool isBalanced(const char *expr) {
    int balance = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(') {
            balance++;
        } else if (expr[i] == ')') {
            balance--;
            if (balance < 0) {
                return false;
            }
        }
    }
    return balance == 0;
}

int main() {
    const char *expression1 = "((()))";
    const char *expression2 = "(()";
    const char *expression3 = ")(";

    printf("%s: %s\n", expression1, isBalanced(expression1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expression2, isBalanced(expression2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", expression3, isBalanced(expression3) ? "Balanced" : "Not Balanced");

    return 0;
}