#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

char *left_rotate(char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return str;
    }

    size_t shift = n % len;
    /* Possible weaknesses found:
     *  Assuming that condition 'shift==0' is not redundant
     */
    if (shift == 0) {
        return str;
    }

    char *temp = (char *)malloc(len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return NULL;
    }

    size_t part1_len = len - shift;
    if (part1_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str + shift, part1_len);
    }

    /* Possible weaknesses found:
     *  part2_len is assigned 'shift' here.
     */
    size_t part2_len = shift;
    /* Possible weaknesses found:
     *  Condition 'part2_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'part2_len>0' is always true
     */
    if (part2_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp + part1_len, str, part2_len);
    }
    temp[len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, temp, len);
    str[len] = '\0';

    free(temp);

    return str;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], SIZE_MAX);
    char *input = (char *)malloc(len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(input, argv[1], len + 1);

    char *endptr;
    errno = 0;
    unsigned long n_ul = strtoul(argv[2], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE || n_ul > SIZE_MAX) {
        fprintf(stderr, "Rotate amount must be a valid non-negative integer\n");
        free(input);
        return EXIT_FAILURE;
    }
    size_t n = (size_t)n_ul;

    char *result = left_rotate(input, n);
    if (result == NULL) {
        fprintf(stderr, "Rotation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(input);

    return EXIT_SUCCESS;
}