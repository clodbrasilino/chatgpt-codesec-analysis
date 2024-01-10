#include <stdio.h>
#include <string.h>

#define MAX_SIZE 200

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    if (!str1 || !str2 || !result || resultSize == 0) {
        return;
    }

    size_t str1Len = strlen(str1);
    size_t str2Len = strlen(str2);

    if (str1Len + str2Len >= resultSize) {
        if (str1Len >= resultSize) {
            str1Len = str2Len = resultSize / 2;
        } else {
            str2Len = resultSize - str1Len - 1;
        }
    }

    memcpy(result, str1, str1Len);
    result[str1Len] = '\0';

    memcpy(result + str1Len, str2, str2Len);
    result[str1Len + str2Len] = '\0';
}

int main() {
    char str1[MAX_SIZE] = "Hello, ";
    char str2[MAX_SIZE] = "world!";
    char result[MAX_SIZE*2] = "";

    concatenateStrings(str1, str2, result, sizeof(result));

    printf("%s\n", result);
    return 0;
}