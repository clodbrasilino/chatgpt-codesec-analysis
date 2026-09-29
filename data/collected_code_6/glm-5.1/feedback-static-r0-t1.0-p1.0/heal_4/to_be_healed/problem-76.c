#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    int min = m < n ? m : n;
    long long total = 0;
    for (int i = 1; i <= min; i++) {
        total += (long long)(m - i + 1) * (n - i + 1);
    }
    return total;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    int m, n;
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(argv[1]) >= 32 || strlen(argv[2]) >= 32) {
        return EXIT_FAILURE;
    }
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buf1[32], buf2[32];
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buf1, argv[1], sizeof(buf1) - 1);
    buf1[sizeof(buf1) - 1] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buf2, argv[2], sizeof(buf2) - 1);
    buf2[sizeof(buf2) - 1] = '\0';
    if (sscanf(buf1, "%d", &m) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(buf2, "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (m <= 0 || n <= 0) {
        return EXIT_FAILURE;
    }
    long long result = count_squares(m, n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}