#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(char *)b - *(char *)a);
}

void find_largest_number(const char *digits, char *result, size_t result_size) {
    size_t len = strnlen(digits, result_size);
    if (len == 0 || len >= result_size) {
        if (result_size > 0) {
            result[0] = '\0';
        }
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(result, digits, result_size - 1);
    result[result_size - 1] = '\0';
    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'digits' can be declared as const array [constVariable]
     */
    char digits[] = "312549";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[50];

    find_largest_number(digits, result, sizeof(result));
    printf("Largest number: %s\n", result);

    return 0;
}