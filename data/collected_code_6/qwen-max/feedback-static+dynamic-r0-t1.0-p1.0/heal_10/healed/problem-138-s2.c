#include <stdio.h>
#include <stdbool.h>

bool isSumOfPowersOfTwo(int n) {
    if (n <= 0) return false;
    int count = 0;
    while (n > 0) {
        if (n & 1) count++;
        n >>= 1;
    }
    return count == 1;
}

int main() {
    int number = 10;
    if (isSumOfPowersOfTwo(number)) {
        printf("%d can be represented as a power of 2.\n", number);
    } else {
        printf("%d cannot be represented as a power of 2.\n", number);
    }
    return 0;
}