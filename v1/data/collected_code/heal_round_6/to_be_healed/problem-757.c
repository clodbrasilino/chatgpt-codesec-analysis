#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(const char* str) {
    if (str == NULL) return 0;
    for (int i = 0; i < (1 << 30); i++) {
        if (str[i] == '\0') return 1;
    }
    return 0;
}

int countReversePairs(const char** strList, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (!isValid(strList[i])) continue;
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int len1 = strlen(strList[i]);
        for (int j = i + 1; j < size; j++) {
            if (!isValid(strList[j])) continue;
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            int len2 = strlen(strList[j]);
            if (len1 != len2) continue;
            int isReverse = 1;
            for (int k = 0; k < len1; k++) {
                if (strList[i][k] != strList[j][len1 - k - 1]) {
                    isReverse = 0;
                    break;
                }
            }
            if (isReverse) count++;
        }
    }
    return count;
}

int main() {
    const char* strList[] = {"hello", "world", "madam", "adam", "hello"};
    int size = sizeof(strList) / sizeof(strList[0]);

    int pairsCount = countReversePairs(strList, size);
    printf("Number of reverse string pairs: %d\n", pairsCount);

    return 0;
}