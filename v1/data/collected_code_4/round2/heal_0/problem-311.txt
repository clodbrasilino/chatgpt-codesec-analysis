#include <stdio.h>

unsigned int setLeftmostUnsetBit(unsigned int num) 
{
    int bitPosition = 0;
    
    while ((num & (1 << bitPosition)) && (bitPosition < sizeof(unsigned int) * 8))
    {
        ++bitPosition;
    }
    
    if (bitPosition < sizeof(unsigned int) * 8) 
    {
        num |= 1 << bitPosition;
    }
    
    return num;
}

int main() 
{
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);
    
    printf("Number after setting leftmost unset bit: %u\n", setLeftmostUnsetBit(num));
    
    return 0;
}