#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 30, got 1
  *  test case 2 failed: expected 2664, got 0
  *  test case 1 failed: expected 273, got 0
  */

static int is_smart_number(uint64_t value)
{
    uint64_t low = 1;
    uint64_t high = value;

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;

        if (mid == value / mid && value % mid == 0) {
            return 1;
        }

        if (mid > value / mid) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;
}

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    uint64_t low;
    uint64_t high;

    if (n == 0 || result == NULL) {
        return 0;
    }

    low = 1;
    high = n;

    while (low <= high) {
        uint64_t mid = low + (high - low) / 2;
        uint64_t count = mid;

        if (is_smart_number(mid)) {
            count--;
        }

        if (count >= n) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    *result = low;
    return 1;
}

int main(void)
{
    char input[128];
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno != 0 || end == input || parsed == 0 || parsed > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        end++;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (!find_nth_smart_number((uint64_t)parsed, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}