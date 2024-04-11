#include <stdio.h>
#include <stdbool.h>

bool areAllBitsUnset(int n, int l, int r) {
    int mask = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
    return (n & mask) == 0;
}

int main() {
    int n = 10;
    int l = 2, r = 3;
    if (areAllBitsUnset(n, l, r))
        printf("All bits are unset in the given range\n");
    else
        printf("All bits are not unset in the given range\n");
    return 0;
}