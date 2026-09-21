#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

void find_largest_number(const char *digits, char *result, size_t result_size) {
    if (digits == NULL || result == NULL || result_size == 0) {
        return;
    }

    size_t len = strnlen(digits, result_size - 1);
    
    if (len == 0) {
        result[0] = '\0';
        return;
    }

    if (len >= result_size) {
        len = result_size - 1;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, digits, len);
    }
    result[len] = '\0';

    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    const char digits[] = "312549";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[64];

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (sizeof(result) <= strlen(digits)) {
        return 1;
    }

    memset(result, 0, sizeof(result));
    find_largest_number(digits, result, sizeof(result));
    printf("Largest number: %s\n", result);

    return 0;
}