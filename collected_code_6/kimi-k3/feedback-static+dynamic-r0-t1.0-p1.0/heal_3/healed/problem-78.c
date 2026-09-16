#include <stdio.h>
#include <limits.h>

int count_odd_set_bits(int n)
{
    int count = 0;
    int i;
    
    if (n < 0) {
        return -1;
    }
    
    for (i = 0; i <= n; i++) {
        int bits = 0;
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
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    result = count_odd_set_bits(n);
    
    if (result == -1) {
        return 1;
    }
    
    printf("%d\n", result);
    
    return 0;
}