#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool strIsValid(const char* str) {
    if (str == NULL) {
        return false;
    }
    while (*str) {
        if (*str != '0' && *str != '1') {
            return false;
        }
        str++;
    }
    return true;
}

int minSwaps(const char* str1, const char* str2) {

    if (!strIsValid(str1) || !strIsValid(str2)) {
        return -1;
    }    

    size_t n = str1 ? strlen(str1) : 0;
    size_t m = str2 ? strlen(str2) : 0;

    if (n != m) {
        return -1;
    }

    int count0 = 0, count1 = 0, mismatch = 0;

    for (size_t i = 0; i < n && str1[i]!='\0' && str2[i]!='\0'; i++) {
        if (str1[i] != str2[i]) {
            mismatch++;
            if (str1[i] == '0') {
                count0++;
            } else {
                count1++;
            }
        }
    }

    if (mismatch % 2 != 0) {
        return -1;
    }

    return mismatch / 2 + (count0 % 2 == 0 ? count0 / 2 : count0 / 2 + 1);
}

int main() {
    const char* str1 = "0110";
    const char* str2 = "1001";

    int swaps = minSwaps(str1, str2);

    printf("Minimum number of swaps required: %d\n", swaps);

    return 0;
}