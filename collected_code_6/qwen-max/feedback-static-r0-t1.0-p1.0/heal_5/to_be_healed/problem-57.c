#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp1[22], temp2[22];
    snprintf(temp1, 22, "%d%d", *(const int *)a, *(const int *)b);
    snprintf(temp2, 22, "%d%d", *(const int *)b, *(const int *)a);
    return strcmp(temp1, temp2) < 0 ? -1 : 1;
}

char* largestNumber(const int *digits, int size) {
    int *sorted_digits = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        sorted_digits[i] = digits[i];
    }

    qsort(sorted_digits, size, sizeof(int), compare);

    char *result = (char *)malloc((size * 11 + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < size; ++i) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char str[12];
        snprintf(str, 12, "%d", sorted_digits[i]);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result, str, 11);
    }

    free(sorted_digits);
    return result;
}

int main() {
    const int digits[] = {3, 30, 34, 5, 9};
    int size = 5;
    char *result = largestNumber(digits, size);
    printf("%s\n", result);
    free(result);
    return 0;
}