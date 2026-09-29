#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     */
    int a = 0, b = 1, c = 0;
    while (a <= n) {
        if (a == n) return true;
        c = a + b;
        a = b;
        b = c;
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (is_in_sequence(num)) {
        printf("Number is in the sequence\n");
    } else {
        printf("Number is not in the sequence\n");
    }
    return 0;
}