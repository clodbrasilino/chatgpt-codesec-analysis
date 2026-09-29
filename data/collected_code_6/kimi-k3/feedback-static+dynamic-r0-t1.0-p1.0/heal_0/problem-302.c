#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int find_msb(uint32_t n)
{
    int msb = -1;
    while (n > 0) {
        n >>= 1;
        msb++;
    }
    return msb;
}

int main(void)
{
    uint32_t num;
    
    if (scanf("%u", &num) != 1) {
        return 1;
    }
    
    int result = find_msb(num);
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        printf("No set bits\n");
    }
    
    return 0;
}