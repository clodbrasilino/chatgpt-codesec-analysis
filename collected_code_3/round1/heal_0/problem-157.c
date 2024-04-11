#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* runLengthEncoding(char* str) {
    int len = strlen(str);
    char* result = (char*)malloc(sizeof(char) * (2 * len + 1));
    int i, count = 1, j = 0;

    for (i = 1; i <= len; i++) {
        if (str[i] == str[i - 1] && i < len) {
            count++;
        } else {
            result[j++] = str[i - 1];
            result[j++] = count + '0';
            count = 1;
        }
    }

    result[j] = '\0';
    return result;
}

int main() {
    char str[] = "aaabbbccc";
    char* encodedStr = runLengthEncoding(str);
    printf("%s\n", encodedStr);
    free(encodedStr);
    return 0;
}