#include <stdio.h>
#include <string.h>

int minSwaps(const char *str1, const char *str2) {
    int len = strlen(str1);
    if (len != strlen(str2)) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int swaps = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

int main() {
    char str1[100], str2[100];

    printf("Enter first binary string: ");
    scanf("%99s", str1);

    printf("Enter second binary string: ");
    scanf("%99s", str2);

    int result = minSwaps(str1, str2);

    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}