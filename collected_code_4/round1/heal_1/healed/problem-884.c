#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

bool checkBitsInRange(int n, int low, int high) {
    if (low < 0 || high > (sizeof(int) * CHAR_BIT - 1)) {
        return false;
    }

    for (int i = low; i <= high; i++) {
        if ((n & (1 << i)) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n = 15;
    int low = 0;
    int high = 3;

    bool result = checkBitsInRange(n, low, high);
    if (result) {
        printf("All bits are set in range\n");
    } else {
        printf("All bits are not set in range\n");
    }
    return 0;
}