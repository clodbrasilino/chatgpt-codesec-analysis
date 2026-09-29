#include <stdio.h>

unsigned int toggleBits(unsigned int num) {
    unsigned int n = sizeof(num) * 8;
    for (int i = 1; i < n - 1; i++) {
        num ^= (1 << i);
    }
    return num;
}

int main() {
    unsigned int x = 23;
    printf("Number before bit toggle: %u\n", x);
    x = toggleBits(x);
    printf("Number after bit toggle: %u\n", x);
    return 0;
}