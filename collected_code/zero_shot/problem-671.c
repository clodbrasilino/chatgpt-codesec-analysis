#include <stdio.h>

unsigned int setRightMostUnsetBit(unsigned int num) {
    // If the number is already all ones, no unset bit exists
    if (num == UINT_MAX) {
        return num;
    }
    
    // Calculate the bitwise negation of the number
    unsigned int negation = ~num;

    // Calculate the bitwise AND of the number and its negation
    unsigned int rightMostUnsetBit = num & negation;
    
    // Return the result
    return rightMostUnsetBit;
}

int main() {
    unsigned int num = 10;
    unsigned int result = setRightMostUnsetBit(num);
    
    printf("The right most unset bit of %u is %u.\n", num, result);
    
    return 0;
}