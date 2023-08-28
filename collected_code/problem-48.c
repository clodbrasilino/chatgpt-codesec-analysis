#include <stdio.h>

void setOddBits(int *num) {
    *num = (*num | 0xAAAAAAAA);
}

int main() {
    int num = 10;
    
    setOddBits(&num);
    
    printf("Number after setting odd bits: %d\n", num);
    
    return 0;
}