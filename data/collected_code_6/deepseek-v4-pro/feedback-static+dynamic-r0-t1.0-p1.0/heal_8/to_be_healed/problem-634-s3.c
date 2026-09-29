#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 64
#define MAX_ALLOWED_VALUE 1000000
#define MIN_ALLOWED_VALUE 1

uint64_t sum_fourth_power_even(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; i++) {
        uint64_t even = 2ULL * i;
        uint64_t square = even * even;
        uint64_t fourth = square * square;
        if (sum > UINT64_MAX - fourth) {
            return UINT64_MAX;
        }
        sum += fourth;
    }
    return sum;
}

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int validate_and_parse_input(const char *input, size_t input_len, long *out_val) {
    if (input_len == 0 || input[0] == '\0') {
        return 0;
    }

    char *endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);

    if (errno != 0 || endptr == input) {
        return 0;
    }

    while (*endptr == ' ' || *endptr == '\t') {
        endptr++;
    }

    if (*endptr != '\n' && *endptr != '\0') {
        return 0;
    }

    if (val < MIN_ALLOWED_VALUE || val > MAX_ALLOWED_VALUE) {
        return 0;
    }

    *out_val = val;
    return 1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (len < sizeof(input) && input[len] != '\0') {
        len++;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0 || (len >= sizeof(input) - 1 && input[sizeof(input) - 2] != '\n')) {
        clear_input_buffer();
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'len>0' is always true
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     */
    if (len > 0 && input[len - 1] != '\n') {
        clear_input_buffer();
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    long val;
    if (!validate_and_parse_input(input, len, &val)) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    int n = (int)val;
    uint64_t result = sum_fourth_power_even(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow detected.\n");
        return EXIT_FAILURE;
    }
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}