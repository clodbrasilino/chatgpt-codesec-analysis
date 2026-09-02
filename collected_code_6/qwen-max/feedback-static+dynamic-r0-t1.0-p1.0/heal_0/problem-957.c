#include <stdio.h>
#include <limits.h>

int findRightmostSetBitPosition(unsigned int num) {
    int position = 1;
    while ((num & 1) == 0 && position <= (sizeof(num) * CHAR_BIT)) {
        num >>= 1;
        position++;
    }
    return (position < (sizeof(num) * CHAR_BIT + 1)) ? position : 0;
}

int main() {
    unsigned int input;
    scanf("%u", &input);
    int pos = findRightmostSetBitPosition(input);
    if (pos != 0) {
        printf("The position of the rightmost set bit is: %d\n", pos);
    } else {
        printf("The number has no set bits.\n");
    }
    return 0;
}