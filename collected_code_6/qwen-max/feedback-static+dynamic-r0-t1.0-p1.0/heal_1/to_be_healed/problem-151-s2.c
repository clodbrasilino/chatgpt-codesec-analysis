#include <stdio.h>
#include <stdbool.h>

bool is_coprime(int a, int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 't' can be reduced. [variableScope]
     */
    int t;
    while (b != 0) {
        t = b;
        b = a % b;
        a = t;
    }
    return a == 1;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        return 1;
    }
    if (is_coprime(num1, num2)) {
        printf("The numbers are co-prime.\n");
    } else {
        printf("The numbers are not co-prime.\n");
    }
    return 0;
}