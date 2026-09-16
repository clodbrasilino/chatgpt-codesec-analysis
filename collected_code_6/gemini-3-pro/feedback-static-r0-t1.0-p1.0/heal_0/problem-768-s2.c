#include <stdio.h>
#include <stdint.h>

int check_odd_parity(uint32_t num) {
    int parity = 0;
    while (num > 0) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return !parity;
}

int main(void) {
    uint32_t number = 42;
    int is_odd = check_odd_parity(number);
    
    if (is_odd) {
        printf("The number %u has odd parity.\n", number);
    } else {
        printf("The number %u does not have odd parity.\n", number);
    }
    
    return 0;
}