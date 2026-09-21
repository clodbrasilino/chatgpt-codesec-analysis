#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(const char *str1, const char *str2, size_t max_len) {
    if (str1 == NULL || str2 == NULL) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[101];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[101];

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    if (areRotations(str1, str2, sizeof(str1))) {
        printf("The strings are rotations of each other.\n");
    } else {
        printf("The strings are not rotations of each other.\n");
    }

    return 0;
}