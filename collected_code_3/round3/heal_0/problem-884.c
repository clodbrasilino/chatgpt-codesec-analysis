#include <stdio.h>
#include <stdbool.h>

bool checkBitsInRange(int num, int l, int r) {
    int mask = ((1 << (r - l + 1)) - 1) << l;
    return (num & mask) == num;
}

int main() {
    int num = 5;
    int l = 0, r = 2;
    if (checkBitsInRange(num, l, r))
        printf("All bits are within the range.\n");
    else
        printf("All bits are not within the range.\n");
    return 0;
}