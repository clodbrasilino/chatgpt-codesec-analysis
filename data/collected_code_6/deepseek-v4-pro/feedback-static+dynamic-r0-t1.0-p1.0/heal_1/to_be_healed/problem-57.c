#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(char *)b - *(char *)a);
}

void largest_number_from_digits(char *digits, char *result) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(digits);
    if (len == 0) {
        result[0] = '\0';
        return;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, digits, len + 1);
    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    char digits[] = "9371458260";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[32];
    largest_number_from_digits(digits, result);
    printf("%s\n", result);
    return 0;
}