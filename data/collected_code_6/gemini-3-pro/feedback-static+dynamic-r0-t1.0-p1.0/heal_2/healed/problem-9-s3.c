#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int findMinimumRotations(const char* str) {
    if (str == NULL) {
        return -1;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return 0;
    }

    char* concatStr = (char*)malloc(2 * len + 1);
    if (concatStr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < len; i++) {
        concatStr[i] = str[i];
    }
    
    for (size_t i = 0; i <= len; i++) {
        concatStr[len + i] = str[i];
    }

    int minRotations = (int)len;

    for (size_t i = 1; i <= len; i++) {
        if (strncmp(concatStr + i, str, len) == 0) {
            minRotations = (int)i;
            break;
        }
    }

    free(concatStr);

    return minRotations == (int)len ? (int)len : minRotations;
}

int main(void) {
    const char* str1 = "abc";
    int result1 = findMinimumRotations(str1);
    printf("%d\n", result1);

    const char* str2 = "aaaa";
    int result2 = findMinimumRotations(str2);
    printf("%d\n", result2);

    const char* str3 = "abab";
    int result3 = findMinimumRotations(str3);
    printf("%d\n", result3);

    return 0;
}