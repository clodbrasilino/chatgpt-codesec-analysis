#include <stdio.h>
#include <limits.h>

unsigned int setRightMostUnsetBit(unsigned int num) {
    if (num == UINT_MAX) {
        return num;
    }
    
    unsigned int negation = ~num;
    unsigned int rightMostUnsetBit = num & negation;
    
    return rightMostUnsetBit;
}

int main() {
    unsigned int num = 10;
    unsigned int result = setRightMostUnsetBit(num);
    
    printf("The right most unset bit of %u is %u.\n", num, result);
    
    return 0;
}