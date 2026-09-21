#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp1[22];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp2[22];
    snprintf(temp1, sizeof(temp1), "%d%d", *(const int *)a, *(const int *)b);
    snprintf(temp2, sizeof(temp2), "%d%d", *(const int *)b, *(const int *)a);
    return strcmp(temp1, temp2) < 0 ? -1 : 1;
}

char* largestNumber(const int *digits, int size) {
    int *sorted_digits = (int *)malloc(size * sizeof(int));
    if (sorted_digits == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        sorted_digits[i] = digits[i];
    }

    qsort(sorted_digits, size, sizeof(int), compare);

    int result_size = 0;
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char str[12];
        snprintf(str, sizeof(str), "%d", sorted_digits[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result_size += strlen(str);
    }
    result_size++; // Add 1 for the null terminator

    char *result = (char *)malloc(result_size);
    if (result == NULL) {
        free(sorted_digits);
        return NULL;
    }
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char str[12];
        snprintf(str, sizeof(str), "%d", sorted_digits[i]);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, str);
    }

    free(sorted_digits);
    return result;
}

int main() {
    const int digits[] = {3, 30, 34, 5, 9};
    int size = 5;
    char *result = largestNumber(digits, size);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }
    return 0;
}