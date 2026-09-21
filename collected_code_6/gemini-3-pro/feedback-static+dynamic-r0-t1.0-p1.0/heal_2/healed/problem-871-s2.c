#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = 0;
    while (len1 < MAX_STR_LEN && str1[len1] != '\0') {
        len1++;
    }

    size_t len2 = 0;
    while (len2 < MAX_STR_LEN && str2[len2] != '\0') {
        len2++;
    }

    if (len1 != len2 || len1 == 0 || len1 == MAX_STR_LEN) {
        return false;
    }

    size_t concatLen = len1 * 2 + 1;
    char *temp = (char *)malloc(concatLen);
    if (temp == NULL) {
        return false;
    }

    snprintf(temp, concatLen, "%s%s", str1, str1);

    bool isRotation = (strstr(temp, str2) != NULL);

    free(temp);

    return isRotation;
}

int main(void) {
    char str1[MAX_STR_LEN + 1];
    char str2[MAX_STR_LEN + 1];

    if (scanf("%4096s", str1) == 1 && scanf("%4096s", str2) == 1) {
        if (areRotations(str1, str2)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    return 0;
}