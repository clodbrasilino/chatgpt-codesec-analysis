#include <stdio.h>
#include <stdbool.h>

bool areAllBitsUnset(int n, int l, int r) {
    int mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
    return !(n & mask);
}

int main() {
    int n = 10, l = 2, r = 3;
    if (areAllBitsUnset(n, l, r))
        printf("All bits in given range are unset\n");
    else
        printf("Not all bits in given range are unset\n");
    return 0;
}