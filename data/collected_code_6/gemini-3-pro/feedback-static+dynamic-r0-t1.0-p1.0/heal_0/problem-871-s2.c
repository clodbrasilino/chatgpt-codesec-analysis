#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 != len2 || len1 == 0) {
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
    const char *str1 = "ABCD";
    const char *str2 = "CDAB";

    if (areRotations(str1, str2)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}