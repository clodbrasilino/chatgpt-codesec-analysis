#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, 2048);
    size_t len2 = strnlen(str2, 2048);

    if (len1 == 2048 || len2 == 2048) {
        return 0;
    }

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    size_t tempSize = 2 * len1 + 1;
    char *temp = (char *)malloc(tempSize);
    if (temp == NULL) {
        return 0;
    }

    int written = snprintf(temp, tempSize, "%s%s", str1, str1);
    if (written < 0 || (size_t)written >= tempSize) {
        free(temp);
        return 0;
    }

    int result = (strstr(temp, str2) != NULL);

    free(temp);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[1024] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[1024] = {0};

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    size_t len1 = strcspn(str1, "\n");
    if (len1 < sizeof(str1)) {
        str1[len1] = '\0';
    }

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    size_t len2 = strcspn(str2, "\n");
    if (len2 < sizeof(str2)) {
        str2[len2] = '\0';
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}