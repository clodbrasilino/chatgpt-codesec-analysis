#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 3
  *  test case 2 failed: expected 3, got 2
  */

static uint64_t minimum_operations(int64_t first, int64_t second)
{
    const uint64_t difference = absolute_difference(first, second);

    return difference / 2U + difference % 2U;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int64_t first;
    int64_t second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first> <second>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_int64(argv[1], &first) ||
        !parse_int64(argv[2], &second)) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}