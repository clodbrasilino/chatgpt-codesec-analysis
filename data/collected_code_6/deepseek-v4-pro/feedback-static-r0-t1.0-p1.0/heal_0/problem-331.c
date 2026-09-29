#include <stdio.h>

int count_unset_bits(unsigned int num) {
    int count = 0;
    unsigned int bits = sizeof(num) * 8;
    
    for (unsigned int i = 0; i < bits; i++) {
        if ((num & (1u << i)) == 0) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    unsigned int number;
    
    printf("Enter a number: ");
    if (scanf("%u", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    int result = count_unset_bits(number);
    printf("Number of unset bits: %d\n", result);
    
    return 0;
}