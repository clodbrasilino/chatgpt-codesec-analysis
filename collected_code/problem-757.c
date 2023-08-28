#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countReversePairs(char** strList, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int len1 = strlen(strList[i]);
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
    char* strList[] = {"hello", "world", "madam", "adam", "hello"};
    int size = sizeof(strList) / sizeof(strList[0]);

    int pairsCount = countReversePairs(strList, size);
    printf("Number of reverse string pairs: %d\n", pairsCount);

    return 0;
}