#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long min_swaps_for_balancing(const char *s);

long min_swaps_for_balancing(const char *s)
{
    long open_count = 0;
    long close_count = 0;
    long swaps = 0;
    long imbalance = 0;
    size_t i;
    size_t len;

    if (s == NULL) {
        return -1L;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);

    for (i = 0U; i < len; i++) {
        if (s[i] == '[') {
            open_count++;
        } else if (s[i] == ']') {
            close_count++;
        } else {
            return -1L;
        }
    }

    if (open_count != close_count) {
        return -1L;
    }

    open_count = 0;
    close_count = 0;

    for (i = 0U; i < len; i++) {
        if (s[i] == '[') {
            open_count++;
            if (imbalance > 0) {
                swaps += imbalance;
                imbalance--;
            }
        } else {
            close_count++;
            imbalance = close_count - open_count;
        }
    }

    return swaps;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    long result;
    size_t len;

    printf("Enter a bracket string (only '[' and ']'): ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    result = min_swaps_for_balancing(buffer);

    if (result < 0) {
        fprintf(stderr, "Error: invalid or unbalanceable input string.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of swaps required: %ld\n", result);

    return EXIT_SUCCESS;
}