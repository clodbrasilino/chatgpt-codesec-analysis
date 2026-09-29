#include <stdio.h>

unsigned int highest_power_of_2(unsigned int n) {
    unsigned int result = 1;
    
    if (n && !(n & (n - 1))) {
        return n;
    }

    while (n) {
        n >>= 1;
        result <<= 1;
    }

    return result >> 1;
}

int main() {
    unsigned int n;
    printf("Enter a number: ");
    scanf("%u", &n);

    printf("Highest power of 2 less than or equal to %u is %u\n", n, highest_power_of_2(n));

    return 0;
}