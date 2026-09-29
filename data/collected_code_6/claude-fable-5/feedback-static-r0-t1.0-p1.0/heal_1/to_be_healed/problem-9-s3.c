#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_min_rotations(const char *str)
{
    size_t len;
    size_t i;
    char *doubled;
    int result;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return -1;
    }

    if (len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    doubled = malloc((2U * len) + 1U);
    if (doubled == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled + len, str, len);
    doubled[2U * len] = '\0';

    result = -1;
    for (i = 1U; i <= len; i++) {
        if (strncmp(doubled + i, str, len) == 0) {
            result = (int)i;
            break;
        }
    }

    free(doubled);
    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    int rotations;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    rotations = find_min_rotations(buffer);
    if (rotations < 0) {
        fprintf(stderr, "Failed to compute rotations\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum rotations required: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}