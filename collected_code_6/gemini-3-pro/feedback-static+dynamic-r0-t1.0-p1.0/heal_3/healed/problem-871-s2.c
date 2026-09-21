#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 4096
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

bool areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }

    size_t len1 = strnlen(str1, MAX_STR_LEN + 1);
    size_t len2 = strnlen(str2, MAX_STR_LEN + 1);

    if (len1 != len2 || len1 == 0 || len1 > MAX_STR_LEN) {
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
    char *str1 = (char *)calloc(MAX_STR_LEN + 1, sizeof(char));
    char *str2 = (char *)calloc(MAX_STR_LEN + 1, sizeof(char));

    if (str1 == NULL || str2 == NULL) {
        free(str1);
        free(str2);
        return EXIT_FAILURE;
    }

    if (scanf("%" STR(MAX_STR_LEN) "s", str1) == 1 && scanf("%" STR(MAX_STR_LEN) "s", str2) == 1) {
        if (areRotations(str1, str2)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }

    free(str1);
    free(str2);

    return EXIT_SUCCESS;
}