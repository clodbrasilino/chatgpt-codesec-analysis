#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

static bool are_rotations(const char *first, const char *second)
{
    size_t length;
    char *combined;
    bool result;

    if (first == NULL || second == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(first);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (length != strlen(second)) {
        return false;
    }

    if (length == 0U) {
        return true;
    }

    if (length > (SIZE_MAX - 1U) / 2U) {
        return false;
    }

    combined = malloc((2U * length) + 1U);
    if (combined == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(combined, first, length);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(combined + length, first, length);
    combined[2U * length] = '\0';

    result = strstr(combined, second) != NULL;
    free(combined);

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[1024];

    if (fgets(first, sizeof(first), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(second, sizeof(second), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    first[strcspn(first, "\r\n")] = '\0';
    second[strcspn(second, "\r\n")] = '\0';

    if (are_rotations(first, second)) {
        puts("The strings are rotations of each other.");
    } else {
        puts("The strings are not rotations of each other.");
    }

    return EXIT_SUCCESS;
}