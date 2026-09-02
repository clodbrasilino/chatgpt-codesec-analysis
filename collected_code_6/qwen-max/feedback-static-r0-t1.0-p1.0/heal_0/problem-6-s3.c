#include <stdio.h>
#include <stdint.h>

int differ_at_one_bit_position(uint32_t a, uint32_t b) {
    uint32_t xor_result = a ^ b;
    return (xor_result != 0) && ((xor_result & (xor_result - 1)) == 0);
}

int main() {
    uint32_t num1, num2;

    printf("Enter the first number: ");
    scanf("%u", &num1);

    printf("Enter the second number: ");
    scanf("%u", &num2);

    if (differ_at_one_bit_position(num1, num2)) {
        printf("The numbers differ at exactly one bit position.\n");
    } else {
        printf("The numbers do not differ at exactly one bit position.\n");
    }

    return 0;
}