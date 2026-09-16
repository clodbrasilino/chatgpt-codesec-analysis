#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a == 0 && b == 0)
        return 0;
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_common_divisor(int a, int b) {
    return gcd(a, b);
}

int main(void) {
    int num1, num2;
    
    printf("Enter two numbers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    int result = find_common_divisor(num1, num2);
    
    if (result == 0) {
        printf("No common divisor found (both numbers are zero)\n");
    } else {
        printf("Greatest common divisor of %d and %d is: %d\n", num1, num2, result);
    }
    
    return EXIT_SUCCESS;
}