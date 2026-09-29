#include <stdio.h>

unsigned int setLeftmostUnsetBit(unsigned int n) {
    if (n == 0)
        return 1;
    int m = 1;
    while (n) {
        n = n >> 1;
        m = m << 1;
    }
    return m;
}

int main() {
    unsigned int n = 21;
    printf("%u", setLeftmostUnsetBit(n));
    return 0;
}