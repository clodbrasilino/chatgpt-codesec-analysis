#include<stdio.h>

int multiply(int a, int b) {
    // Exit condition for recursion.
    if(b == 0) {
        return 0;
    }

    // Check for negative inputs, then recurse.
    if(b > 0) {
        return (a + multiply(a, b-1));
    }

    // For negative inputs, the above condition becomes true when we reach 0,
    // so we stop the recursion, multiplying a by -1 for each decrease in b.
    if(b < 0) {
        return -multiply(a, -b);
    }
    return 0;
}

int main() {
    int num1, num2;
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    printf("The product is: %d", multiply(num1, num2));
    return 0;
}