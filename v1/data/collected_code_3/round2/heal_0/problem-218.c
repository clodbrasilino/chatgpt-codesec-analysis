#include <stdio.h>
#include <stdlib.h>

int minOperations(int a, int b) {
    int count = 0;
    while(a != b) {
        if(a > b) {
            a -= b;
        } else {
            b -= a;
        }
        count++;
    }
    return count;
}

int main() {
    int num1, num2;
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    printf("Minimum operations required to make two numbers equal: %d\n", minOperations(num1, num2));
    return 0;
}