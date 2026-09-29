#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool checkBitsInRange(unsigned int num, unsigned int start, unsigned int end) {
    if (start >= 32 || end >= 32 || start > end) return false;
    unsigned int mask = ((1U << (end - start + 1)) - 1) << start;
    return (num & mask) == mask;
}

int main() {
    unsigned int num, start, end;
    printf("Enter the number: ");
    scanf("%u", &num);
    printf("Enter the start and end positions: ");
    scanf("%u %u", &start, &end);

    if (checkBitsInRange(num, start, end)) {
        printf("All bits are set in the given range.\n");
    } else {
        printf("Not all bits are set in the given range.\n");
    }

    return 0;
}