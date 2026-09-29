#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int countReversePairs(const char** strList, int size) {
    assert(strList != NULL && size > 0);
    int count = 0;
    for (int i = 0; i < size; i++) {
        if(strList[i] == NULL) continue;
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int len1 = strlen(strList[i]);
        for (int j = i + 1; j < size; j++) {
            if(strList[j] == NULL) continue;
            /* Possible weaknesses found:
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
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