#include <stdio.h>
#include <stdbool.h>

bool checkBitsRange(int num, int left, int right) {
    int mask = ((1 << (right - left + 1)) - 1) << (left - 1);
    return (num & mask) == num;
}

int main() {
    int num = 5;
    int left = 1;
    int right = 3;

    if (checkBitsRange(num, left, right)) {
        printf("All bits are within the given range.\n");
    } else {
        printf("All bits are not within the given range.\n");
    }

    return 0;
}