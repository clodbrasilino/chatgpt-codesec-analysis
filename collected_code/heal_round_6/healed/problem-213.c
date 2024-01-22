#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 200

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    if (!str1 || !str2 || !result || resultSize == 0) {
        return;
    }

    size_t str1Len = strnlen(str1, resultSize);
    size_t str2Len = strnlen(str2, resultSize);

    if (str1Len + str2Len >= resultSize) {
        if (str1Len >= resultSize) {
            str1Len = str2Len = resultSize / 2;
        } else {
            str2Len = resultSize - str1Len - 1;
        }
    }

    snprintf(result, str1Len+1, "%s", str1);
    snprintf(result + str1Len, str2Len+1, "%s", str2);
}

int main() {
    char *str1 = malloc(MAX_SIZE);
    char *str2 = malloc(MAX_SIZE);
    char *result = malloc(MAX_SIZE*2);

    if(str1 != NULL && str2 != NULL && result!= NULL) {

        snprintf(str1, MAX_SIZE, "%s", "Hello, ");
        snprintf(str2, MAX_SIZE, "%s", "world!");

        concatenateStrings(str1, str2, result, MAX_SIZE*2);

        printf("%s\n", result);
        free(str1);
        free(str2);
        free(result);
    }
    return 0;
}