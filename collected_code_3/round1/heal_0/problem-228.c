#include <stdio.h>
#include <stdbool.h>

bool areAllBitsUnsetInRange(int num, int l, int r) {
    int mask = ((1 << (r - l + 1)) - 1) << l;
    return (num & mask) == 0;
}

int main() {
    int num = 0;
    int l = 0;
    int r = 3;
    if (areAllBitsUnsetInRange(num, l, r)) {
        printf("All bits are unset in the given range.\n");
    } else {
        printf("All bits are not unset in the given range.\n");
    }
    return 0;
}