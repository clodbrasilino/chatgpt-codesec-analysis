#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2, size_t max_len) {
    if (str1 == NULL || str2 == NULL || max_len == 0) {
        return 0;
    }

    size_t len1 = strnlen(str1, max_len);
    size_t len2 = strnlen(str2, max_len);

    if (len1 != len2 || len1 == 0 || len1 >= max_len || len2 >= max_len) {
        return 0;
    }

    if (len1 > (SIZE_MAX - 1) / 2) {
        return 0;
    }

    size_t concatLen = 2 * len1 + 1;
    char *concat = (char *)malloc(concatLen);

    if (concat == NULL) {
        return 0;
    }

    int written = snprintf(concat, concatLen, "%s%s", str1, str1);
    if (written < 0 || (size_t)written >= concatLen) {
        free(concat);
        return 0;
    }

    int result = (strstr(concat, str2) != NULL);

    free(concat);
    concat = NULL;

    return result;
}

int main(void) {
    char *str1 = NULL;
    char *str2 = NULL;
    size_t size1 = 0;
    size_t size2 = 0;
    ssize_t read1, read2;

    printf("Enter first string: ");
    read1 = getline(&str1, &size1, stdin);
    if (read1 == -1) {
        free(str1);
        return 1;
    }
    if (read1 > 0 && str1[read1 - 1] == '\n') {
        str1[read1 - 1] = '\0';
    }

    printf("Enter second string: ");
    read2 = getline(&str2, &size2, stdin);
    if (read2 == -1) {
        free(str1);
        free(str2);
        return 1;
    }
    if (read2 > 0 && str2[read2 - 1] == '\n') {
        str2[read2 - 1] = '\0';
    }

    size_t max_len = (size1 > size2) ? size1 : size2;

    if (areRotations(str1, str2, max_len)) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    free(str1);
    free(str2);

    return 0;
}