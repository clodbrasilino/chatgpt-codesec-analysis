#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Possible weaknesses found:
 *  Parameter 'expression' can be declared as pointer to const [constParameterPointer]
 */
bool is_balanced(char *expression) {
    int stack[100];
    int top = -1;
    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            stack[++top] = expression[i];
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            if (top == -1) return false;
            char c = stack[top--];
            if ((expression[i] == ')' && c != '(') ||
                (expression[i] == ']' && c != '[') ||
                (expression[i] == '}' && c != '{')) {
                return false;
            }
        }
    }
    return top == -1;
}

int main() {
    char *test1 = "(a + b) * (c + d)";
    char *test2 = "((a + b)";
    char *test3 = "{[()]}";
    char *test4 = "{[}]";

    printf("%s: %s\n", test1, is_balanced(test1) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", test2, is_balanced(test2) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", test3, is_balanced(test3) ? "Balanced" : "Not Balanced");
    printf("%s: %s\n", test4, is_balanced(test4) ? "Balanced" : "Not Balanced");

    return 0;
}