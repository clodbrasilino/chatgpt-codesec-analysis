#include <stdio.h>
#include <stdbool.h>

bool checkBitsInRange(int num, int lower, int upper) {
    int mask = ((1 << (upper - lower + 1)) - 1) << lower;
    return (num & mask) == num;
}

int main() {
    int num = 5;
    int lower = 0;
    int upper = 2;

    if(checkBitsInRange(num, lower, upper)) {
        printf("All bits are within the given range.\n");
    } else {
        printf("All bits are not within the given range.\n");
    }

    return 0;
}