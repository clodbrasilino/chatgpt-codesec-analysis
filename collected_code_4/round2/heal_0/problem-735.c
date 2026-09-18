#include <stdio.h>
#define FIRST_BIT (1 << ((sizeof(int) * 8) - 1))
#define LAST_BIT 1

unsigned int toggleBits(unsigned int num) {
    return (~(num) | FIRST_BIT | LAST_BIT) & (num | ~FIRST_BIT | ~LAST_BIT);
}

int main(void) {
    unsigned int result = toggleBits(285);
    printf("%u", result);
    
    return 0;
}