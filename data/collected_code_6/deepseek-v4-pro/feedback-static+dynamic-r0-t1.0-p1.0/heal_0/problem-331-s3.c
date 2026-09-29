#include <stdio.h>

int count_unset_bits(unsigned int num) {
    int count = 0;
    unsigned int mask = 1;
    int bits = sizeof(num) * 8;
    
    for (int i = 0; i < bits; i++) {
        if ((num & mask) == 0) {
            count++;
        }
        mask <<= 1;
    }
    
    return count;
}

int main(void) {
    unsigned int number;
    
    printf("Enter a number: ");
    if (scanf("%u", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Number of unset bits: %d\n", count_unset_bits(number));
    
    return 0;
}