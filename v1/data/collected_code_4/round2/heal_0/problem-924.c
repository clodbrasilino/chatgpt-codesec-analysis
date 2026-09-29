#include <stdio.h>

int maximum(int num1, int num2) {
    if(num1 > num2)
        return num1;
    else
        return num2;
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d%d", &a, &b); 
    printf("Maximum number is: %d", maximum(a, b));
    return 0;
}