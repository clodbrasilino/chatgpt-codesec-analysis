#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_SIZE 1024U

long min_swaps_for_balancing(const char *s, size_t max_len);
static int read_line(char *buffer, size_t size);

long min_swaps_for_balancing(const char *s, size_t max_len)
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

    if (max_len == 0U) {
        return -1L;
    }

    len = strnlen(s, max_len);
    if (len >= max_len) {
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

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if ((buffer == NULL) || (size < 2U) || (size > (size_t)INT_MAX)) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1U] = '\0';

    len = strnlen(buffer, size);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
        return 0;
    }

    if (len == (size - 1U)) {
        int ch;
        int truncated = 0;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
            if ((ch != EOF) && (ch != '\n')) {
                truncated = 1;
            }
        } while ((ch != EOF) && (ch != '\n'));

        if (truncated != 0) {
            return -2;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
    long result;
    int status;

    (void)memset(buffer, 0, sizeof(buffer));

    printf("Enter a bracket string (only '[' and ']'): ");

    status = read_line(buffer, sizeof(buffer));
    if (status == -2) {
        fprintf(stderr, "Error: input too long.\n");
        return EXIT_FAILURE;
    }
    if (status != 0) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    result = min_swaps_for_balancing(buffer, sizeof(buffer));

    if (result < 0) {
        fprintf(stderr, "Error: invalid or unbalanceable input string.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of swaps required: %ld\n", result);

    return EXIT_SUCCESS;
}