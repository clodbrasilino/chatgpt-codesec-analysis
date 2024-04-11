#include <stdio.h>

int countUnsetBits(unsigned int n) {
    int count = 0;
    while (n) {
        count += !(n & 1);
        n >>= 1;
    }
    return count;
}

int main() {
    unsigned int n = 15;
    printf("Number of unset bits in %d is %d\n", n, countUnsetBits(n));
    return 0;
}