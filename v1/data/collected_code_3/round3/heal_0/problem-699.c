#include <stdio.h>
#include <string.h>

int minSwaps(char *binary1, char *binary2, int n) {
    int count1 = 0, count2 = 0;
    int result = 0;

    for (int i = 0; i < n; i++) {
        if (binary1[i] != binary2[i]) {
            if (binary1[i] == '1')
                count1++;
            else
                count2++;
        }
    }

    result = (count1 + count2) / 2;

    if (count1 % 2 != count2 % 2) {
        return -1;
    }

    return result;
}

int main() {
    char binary1[] = "1100";
    char binary2[] = "0011";
    int n = strlen(binary1);

    int result = minSwaps(binary1, binary2, n);

    if (result != -1) {
        printf("Minimum number of swaps required = %d\n", result);
    } else {
        printf("Conversion is not possible\n");
    }

    return 0;
}