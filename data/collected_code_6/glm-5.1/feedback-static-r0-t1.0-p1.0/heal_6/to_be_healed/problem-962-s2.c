#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }

    if (l <= 0) {
        l = 1;
    }

    if (l % 2 != 0) {
        l++;
    }

    if (r % 2 != 0) {
        r--;
    }

    if (l > r) {
        return 0;
    }

    long long count = ((r - l) / 2) + 1;
    return count * (l + r) / 2;
}

int main(int argc, char *argv[]) {
    long long l, r;
    char *endptr1, *endptr2;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf1[22];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf2[22];
    size_t len1, len2;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <l> <r>\n", argv[0]);
        return EXIT_FAILURE;
    }

    len1 = strnlen(argv[1], 21);
    if (len1 > 20) {
        fprintf(stderr, "Invalid input for l\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf1, argv[1], len1);
    buf1[len1] = '\0';

    len2 = strnlen(argv[2], 21);
    if (len2 > 20) {
        fprintf(stderr, "Invalid input for r\n");
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buf2, argv[2], len2);
    buf2[len2] = '\0';

    errno = 0;
    l = strtoll(buf1, &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0') {
        fprintf(stderr, "Invalid input for l\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    r = strtoll(buf2, &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0') {
        fprintf(stderr, "Invalid input for r\n");
        return EXIT_FAILURE;
    }

    if (l < 0 || r < 0) {
        fprintf(stderr, "Inputs must be natural numbers\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", sum_even_natural_numbers(l, r));

    return EXIT_SUCCESS;
}