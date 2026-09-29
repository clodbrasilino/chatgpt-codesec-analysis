#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int is_demlo(int n)
{
    if (n <= 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[12];
    int len = snprintf(buffer, sizeof(buffer), "%d", n);
    if (len < 0 || (size_t)len >= sizeof(buffer)) {
        return 0;
    }

    if (len % 2 == 0) {
        return 0;
    }

    int mid = len / 2;
    for (int i = 0; i < mid; i++) {
        if (buffer[i] != '1' + i) {
            return 0;
        }
    }
    for (int i = mid; i < len; i++) {
        if (buffer[i] != '1' + (len - 1 - i)) {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *endptr;
    long val;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);

    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return EXIT_FAILURE;
    }

    if (endptr == input) {
        return EXIT_FAILURE;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' || *endptr == '\r') {
        endptr++;
    }

    if (*endptr != '\0') {
        return EXIT_FAILURE;
    }

    if (is_demlo((int)val)) {
        printf("%d is a Demlo number\n", (int)val);
    } else {
        printf("%d is not a Demlo number\n", (int)val);
    }

    return EXIT_SUCCESS;
}