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

int main(void)
{
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
    }

    len = strnlen(buffer, sizeof(buffer));

    result = min_swaps_for_balancing(buffer, len);

    if (result < 0) {
        fprintf(stderr, "Error: invalid or unbalanceable input string.\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of swaps required: %ld\n", result);

    return EXIT_SUCCESS;
}