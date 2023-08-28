#include <stdbool.h>

bool checkBitsInRange(int num, int startBit, int endBit) {
    int range = (1 << (endBit - startBit + 1)) - 1;
    int maskedBits = (num >> startBit) & range;

    return (maskedBits == range);
}