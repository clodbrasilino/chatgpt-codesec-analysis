#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwapsToConvert(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) {
        return -1;
    }

    int len = strlen(str1);
    int count1_1 = 0, count2_1 = 0;
    int mismatch_10 = 0, mismatch_01 = 0;

    for (int i = 0; i < len; i++) {
        if (str1[i] == '1') count1_1++;
        if (str2[i] == '1') count2_1++;

        if (str1[i] != str2[i]) {
            if (str1[i] == '1') {
                mismatch_10++;
            } else {
                mismatch_01++;
            }
        }
    }

    if (count1_1 != count2_1) {
        return -1;
    }

    if (mismatch_10 != mismatch_01) {
        return -1;
    }

    return mismatch_10;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <binary_string1> <binary_string2>\n", argv[0]);
        return 1;
    }

    const char *str1 = argv[1];
    const char *str2 = argv[2];

    int result = minSwapsToConvert(str1, str2);
    
    if (result == -1) {
        printf("Conversion not possible\n");
    } else {
        printf("Minimum swaps needed: %d\n", result);
    }

    return 0;
}