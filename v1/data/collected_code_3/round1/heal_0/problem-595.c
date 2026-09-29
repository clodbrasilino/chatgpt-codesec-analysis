#include <stdio.h>
#include <string.h>

int minSwaps(char *binaryStr1, char *binaryStr2, int len) {
    int count = 0;
    int i = 0;
    while (i < len) {
        if (binaryStr1[i] != binaryStr2[i]) {
            int swapPos = i;
            while (binaryStr1[swapPos] != binaryStr2[i]) {
                swapPos++;
            }
            char temp = binaryStr1[swapPos];
            binaryStr1[swapPos] = binaryStr1[i];
            binaryStr1[i] = temp;
            count++;
        }
        i++;
    }
    return count;
}

int main() {
    char binaryStr1[] = "11001";
    char binaryStr2[] = "01110";
    int len = strlen(binaryStr1);
    printf("Minimum swaps required = %d", minSwaps(binaryStr1, binaryStr2, len));
    return 0;
}