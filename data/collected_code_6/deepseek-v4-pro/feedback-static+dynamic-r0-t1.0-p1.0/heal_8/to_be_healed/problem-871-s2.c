#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_STRING_LENGTH 100

int areRotations(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    size_t len1 = strnlen(str1, MAX_STRING_LENGTH + 1);
    size_t len2 = strnlen(str2, MAX_STRING_LENGTH + 1);

    if (len1 != len2) {
        return 0;
    }

    if (len1 == 0) {
        return 1;
    }

    if (len1 > MAX_STRING_LENGTH) {
        return 0;
    }

    size_t temp_size = 2 * len1 + 1;
    
    char *temp = (char *)malloc(temp_size);
    if (temp == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str1, len1);
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

static void clearInputBuffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static size_t readString(char *buffer, size_t bufferSize, size_t maxLength) {
    if (fgets(buffer, bufferSize, stdin) == NULL) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[bufferSize - 1] = '\0';
    size_t len = strnlen(buffer, bufferSize);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else {
        if (len == bufferSize - 1) {
            clearInputBuffer();
        }
    }

    if (len > maxLength) {
        buffer[maxLength] = '\0';
        len = maxLength;
    }

    return len;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[MAX_STRING_LENGTH + 2];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[MAX_STRING_LENGTH + 2];

    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));

    printf("Enter first string: ");
    size_t len1 = readString(str1, sizeof(str1), MAX_STRING_LENGTH);

    if (len1 > MAX_STRING_LENGTH) {
        return 1;
    }

    printf("Enter second string: ");
    size_t len2 = readString(str2, sizeof(str2), MAX_STRING_LENGTH);

    if (len2 > MAX_STRING_LENGTH) {
        return 1;
    }

    if (areRotations(str1, str2)) {
        printf("Strings are rotations of each other\n");
    } else {
        printf("Strings are not rotations of each other\n");
    }

    return 0;
}