#include <stdio.h>
#include <stdbool.h>

bool is_hex_even(unsigned int num) {
    return (num & 1) == 0;
}

int main() {
    unsigned int hex_number;
    printf("Enter a hexadecimal number: ");
    scanf("%x", &hex_number);
    
    if (is_hex_even(hex_number)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }
    
    return 0;
}