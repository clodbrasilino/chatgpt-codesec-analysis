#include <stdio.h>
#include <string.h>

int minSwaps(char *binaryStr1, char *binaryStr2, int n) {
    int count1 = 0;
    int count2 = 0;
    int count = 0;
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (binaryStr1[i] != binaryStr2[i]) {
            if (binaryStr1[i] == '1') {
                count1++;
            } else {
                count2++;
            }
        }

        if (binaryStr1[i] == '1') {
            count++;
        }
        if (binaryStr2[i] == '1') {
            count--;
        }
    }

    if (count != 0) {
        return -1;
    }

    result = (count1 > count2) ? count1 : count2;

    return result;
}

int main() {
    char binaryStr1[] = "1100";
    char binaryStr2[] = "0011";
    int n = strlen(binaryStr1);

    int result = minSwaps(binaryStr1, binaryStr2, n);

    if (result != -1) {
        printf("Minimum number of swaps required is %d\n", result);
    } else {
        printf("Conversion is not possible\n");
    }

    return 0;
}