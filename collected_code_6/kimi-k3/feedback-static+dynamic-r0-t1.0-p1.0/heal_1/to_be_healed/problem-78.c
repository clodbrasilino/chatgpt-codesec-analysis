#include <stdio.h>
#include <limits.h>

int count_odd_set_bits(int n)
{
    int count = 0;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'bits' can be reduced. [variableScope]
     */
    int bits;
    
    if (n < 0) {
        return -1;
    }
    
    for (i = 0; i <= n; i++) {
        bits = 0;
        int num = i;
        while (num > 0) {
            bits += num & 1;
            num >>= 1;
        }
        if (bits % 2 != 0) {
            count++;
        }
    }
    
    return count;
}

int main(void)
{
    int n;
    int result;
    
    printf("Enter a number: ");
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    result = count_odd_set_bits(n);
    
    if (result == -1) {
        printf("Invalid input: negative number\n");
        return 1;
    }
    
    printf("Number of integers with odd set bits: %d\n", result);
    
    return 0;
}