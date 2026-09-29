#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_non_empty_substrings(uint64_t length, uint64_t *count)
{
    uint64_t first;
    uint64_t second;

    if (count == NULL) {
        return -1;
    }

    first = length;
    /* Possible weaknesses found:
     *  Assignment 'second=length+1U', assigned value is greater than 0
     */
    second = length + 1U;

    /* Possible weaknesses found:
     *  Condition 'second==0U' is always false
     *  Condition 'second==0U' is always false [knownConditionTrueFalse]
     */
    if (second == 0U) {
        return -1;
    }

    if ((first & 1U) == 0U) {
        first /= 2U;
    } else {
        second /= 2U;
    }

    if (second != 0U && first > UINT64_MAX / second) {
        return -1;
    }

    *count = first * second;
    return 0;
}

int main(void)
{
    uint64_t length = 0U;
    uint64_t count;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == UINT64_MAX) {
            return EXIT_FAILURE;
        }
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (count_non_empty_substrings(length, &count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}