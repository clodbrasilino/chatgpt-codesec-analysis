#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(const char* str, int maxSize) {
    if(str == NULL || str[maxSize - 1] != '\0') return 0;
    
    return 1;
}

int countReversePairs(const char** strList, int size, int* strLengths) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if (!isValid(strList[i], strLengths[i])) continue;

        int len1 = strLengths[i] - 1;
        for (int j = i + 1; j < size; j++) {
            if (!isValid(strList[j], strLengths[j])) continue;

            int len2 = strLengths[j] - 1;
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
    const char* strList[] = {"hello", "world", "madam", "adam","hello"};
    int sizes[] = {6,6,6,5,6};
    int size = sizeof(strList) / sizeof(strList[0]);

    int pairsCount = countReversePairs(strList, size, sizes);
    printf("Number of reverse string pairs: %d\n", pairsCount);

    return 0;
}