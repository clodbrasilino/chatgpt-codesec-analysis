#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int find_min_rotations(const char *str, size_t max_len)
{
    size_t len;
    size_t i;
    size_t doubled_size;
    char *doubled;
    int result;

    if (str == NULL || max_len == 0U) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == 0U || len == max_len) {
        return -1;
    }

    if (len > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    if (len > (size_t)INT_MAX) {
        return -1;
    }

    /* Possible weaknesses found:
     *  doubled_size is assigned '(2U*len)+1U' here.
     */
    doubled_size = (2U * len) + 1U;

    doubled = malloc(doubled_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (doubled == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition '(2U*len)<doubled_size' is always true
     *  Condition '(2U*len)<doubled_size' is always true [knownConditionTrueFalse]
     */
    if ((len <= doubled_size - 1U) && ((2U * len) < doubled_size)) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(doubled, str, len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(doubled + len, str, len);
        doubled[2U * len] = '\0';
    } else {
        free(doubled);
        return -1;
    }

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

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer)) {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    rotations = find_min_rotations(buffer, sizeof(buffer));
    if (rotations < 0) {
        fprintf(stderr, "Failed to compute rotations\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum rotations required: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}