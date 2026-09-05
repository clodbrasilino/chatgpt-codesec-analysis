#include <stdio.h>
#include <limits.h>

int countUnsetBits(unsigned int num)
{
    int count = 0;
    int totalBits = sizeof(num) * CHAR_BIT;
    
    for (int i = 0; i < totalBits; i++)
    {
        if ((num & (1U << i)) == 0)
        {
            count++;
        }
    }
    
    return count;
}

int main(void)
{
    unsigned int num;
    
    if (scanf("%u", &num) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Unset bits: %d\n", countUnsetBits(num));
    
    return 0;
}