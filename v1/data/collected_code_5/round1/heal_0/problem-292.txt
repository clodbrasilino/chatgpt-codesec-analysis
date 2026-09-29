#include <stdio.h>

float find_quotient(int num1, int num2) {
    if(num2 == 0) {
        printf("Error! Division by zero is not allowed.\n");
        return 0;
    }
    return (float)num1 / num2;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d%d", &num1, &num2);

    float quotient = find_quotient(num1, num2);
    if(num2 != 0)
    {
        printf("The quotient is %.2f\n", quotient);
    }

    return 0;
}