#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 2664, got 0
  *  test case 0 failed: expected 30, got 0
  *  test case 1 failed: expected 273, got 0
  */

static int is_smart_number(uint64_t value)
{
    return value != 0 && value % 3 == 0;
}

static int find_nth_smart_number(uint64_t n, uint64_t *result)
{
    uint64_t candidate = 0;
    uint64_t count = 0;

    if (n == 0 || result == NULL) {
        return 0;
    }

    while (count < n) {
        if (candidate > UINT64_MAX - 3) {
            return 0;
        }

        candidate += 3;

        if (is_smart_number(candidate)) {
            ++count;
        }
    }

    *result = candidate;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 || parsed > UINT64_MAX) {
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