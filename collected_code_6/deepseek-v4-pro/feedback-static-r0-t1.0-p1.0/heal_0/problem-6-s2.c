#include <stdio.h>
#include <stdbool.h>

bool differ_by_one_bit(unsigned int a, unsigned int b) {
    unsigned int diff = a ^ b;
    return diff != 0 && (diff & (diff - 1)) == 0;
}

int main(void) {
    unsigned int num1, num2;
    
    printf("Enter first number: ");
    scanf("%u", &num1);
    printf("Enter second number: ");
    scanf("%u", &num2);
    
    if (differ_by_one_bit(num1, num2)) {
        printf("The numbers differ at exactly one bit position\n");
    } else {
        printf("The numbers do not differ at exactly one bit position\n");
    }
    
    return 0;
}