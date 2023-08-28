#include <stdbool.h>

bool checkBitsUnset(int num, int start, int end) {
    int mask = ((1 << (end - start + 1)) - 1) << start;
    return (num & mask) == 0;
}