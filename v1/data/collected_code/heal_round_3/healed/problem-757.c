#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int isNullorNotTerminated(const char* str) {
    if (str == NULL) return 1;
    
    for (int i = 0; i < (1 << 30); i++) {
        if (str[i] == '\0') return 0;
    }
    return 1;
}

int countReversePairs(const char** strList, int size) {
    assert(strList != NULL && size > 0);
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (isNullorNotTerminated(strList[i])) continue;
        int len1 = strlen(strList[i]);
        for (int j = i + 1; j < size; j++) {
            if (isNullorNotTerminated(strList[j])) continue;
            int len2 = strlen(strList[j]);
            if (len1 != len2) {
                continue;
            }
            int isReverse = 1;
            for (int k = 0; k < len1; k++) {
                if (strList[i][k] != strList[j][len1 - k - 1]) {
                    isReverse = 0;
                    break;
                }
            }
            if (isReverse) {
                count++;
            }
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