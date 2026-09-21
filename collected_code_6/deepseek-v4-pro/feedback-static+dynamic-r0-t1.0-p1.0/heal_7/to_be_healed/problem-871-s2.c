#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, 101);
    size_t len2 = strnlen(str2, 101);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    if (len1 > 100) {
        return 0;
    }

    /* Possible weaknesses found:
     *  temp_size is assigned '2*len1+1' here.
     */
    size_t temp_size = 2 * len1 + 1;
    
    /* Possible weaknesses found:
     *  Condition 'temp_size<=2*len1' is always false
     *  Condition 'temp_size<=2*len1' is always false [knownConditionTrueFalse]
     */
    if (temp_size <= 2 * len1) {
        return 0;
    }

    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return 0;
    }

    if (temp_size < len1 + 1) {
        free(temp);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str1, len1);

    if (temp_size < 2 * len1 + 1) {
        free(temp);
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp + len1, str1, len1);
    temp[2 * len1] = '\0';

    const char *found = strstr(temp, str2);
    int result = (found != NULL);

    free(temp);
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[102] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[102] = {0};

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }

    str1[sizeof(str1) - 1] = '\0';
    size_t len1 = strnlen(str1, sizeof(str1) - 1);
    if (len1 > 0 && str1[len1 - 1] == '\n') {
        str1[len1 - 1] = '\0';
        len1--;
    } else {
        if (len1 == sizeof(str1) - 1 && str1[len1] == '\0') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
    }

    if (len1 > 100) {
        return 1;
    }

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }

    str2[sizeof(str2) - 1] = '\0';
    size_t len2 = strnlen(str2, sizeof(str2) - 1);
    if (len2 > 0 && str2[len2 - 1] == '\n') {
        str2[len2 - 1] = '\0';
        len2--;
    } else {
        if (len2 == sizeof(str2) - 1 && str2[len2] == '\0') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
    }

    if (len2 > 100) {
        return 1;
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}