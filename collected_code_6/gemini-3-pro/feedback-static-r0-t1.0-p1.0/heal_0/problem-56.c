#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

bool isOneLessTwiceReverse(uint32_t num) {
    uint32_t temp = num;
    uint32_t reversed = 0;

    if (num == 0) {
        return false;
    }

    while (temp > 0) {
        uint32_t digit = temp % 10;
        
        if (reversed > (UINT32_MAX - digit) / 10) {
            return false;
        }
        
        reversed = reversed * 10 + digit;
        temp /= 10;
    }

    if (reversed > UINT32_MAX / 2) {
        return false;
    }

    return num == (2 * reversed - 1);
}

int main(void) {
    uint32_t testCases[] = {73, 11, 0, 19, 45, 121};
    size_t numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numTestCases; i++) {
        uint32_t num = testCases[i];
        if (isOneLessTwiceReverse(num)) {
            printf("%u is one less than twice its reverse.\n", num);
        } else {
            printf("%u is not one less than twice its reverse.\n", num);
        }
    }

    return 0;
}