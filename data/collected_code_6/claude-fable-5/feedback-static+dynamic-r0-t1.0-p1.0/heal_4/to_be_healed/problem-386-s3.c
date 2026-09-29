#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024U

long min_swaps_for_balancing(const char *s, size_t len);

long min_swaps_for_balancing(const char *s, size_t len)
{
    long open_count = 0;
    long close_count = 0;
    long swaps = 0;
    long imbalance = 0;
    size_t i;

    if (s == NULL) {
        return -1L;
    }

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

static int discard_remaining_input(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    long result;
    size_t len;
    char *newline;

    printf("Enter a bracket string (only '[' and ']'): ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    newline = memchr(buffer, '\n', sizeof(buffer));
    if (newline != NULL) {
        *newline = '\0';
    } else {
        if (discard_remaining_input() == EOF && ferror(stdin)) {
            fprintf(stderr, "Error: failed to read input.\n");
            return EXIT_FAILURE;
        }
    }

    len = strnlen(buffer, sizeof(buffer));

    if (len == 0U) {
        fprintf(stderr, "Error: empty input string.\n");
        return EXIT_FAILURE;
    }

    result = min_swaps_for_balancing(buffer, len);

    if (result < 0) {
        fprintf(stderr, "Error: invalid or unbalanceable input string.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of swaps required: %ld\n", result);

    return EXIT_SUCCESS;
}