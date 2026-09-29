#include <stdio.h>
#include <math.h>

unsigned int nextPowerOf2(unsigned int n) {
    if(n && !(n & (n - 1)))
        return n;
    unsigned int count = 0;
    while(n != 0) {
        n >>= 1;
        count += 1;
    }
    return 1 << count;
}

int main() {
    unsigned int n = 0;
    printf("Enter a number: ");
    scanf("%u", &n);
    printf("Next power of 2 is: %u\n", nextPowerOf2(n));
    return 0;
}