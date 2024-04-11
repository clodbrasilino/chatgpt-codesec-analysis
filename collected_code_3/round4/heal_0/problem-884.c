#include <stdio.h>
#include <stdbool.h>

bool checkBitsInRange(int num, int low, int high) {
    int mask = ((1 << (high - low + 1)) - 1) << low;
    return (num & mask) == num;
}

int main() {
    int num = 5;
    int low = 0;
    int high = 2;

    if(checkBitsInRange(num, low, high)) {
        printf("All bits are within the range.\n");
    } else {
        printf("All bits are not within the range.\n");
    }

    return 0;
}