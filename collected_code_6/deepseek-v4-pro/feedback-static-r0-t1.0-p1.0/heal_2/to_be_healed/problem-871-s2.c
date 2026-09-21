#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int areRotations(const char *str1, const char *str2) {
    size_t len1 = strnlen(str1, 100);
    size_t len2 = strnlen(str2, 100);

    if (len1 != len2 || len1 == 0) {
        return 0;
    }

    size_t tempSize = 2 * len1 + 1;
    char *temp = (char *)malloc(tempSize);
    if (temp == NULL) {
        return 0;
    }

    if (snprintf(temp, tempSize, "%s%s", str1, str1) < 0) {
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
    char str1[101] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[101] = {0};

    printf("Enter first string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", str1) != 1) {
        return 1;
    }

    printf("Enter second string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%100s", str2) != 1) {
        return 1;
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}