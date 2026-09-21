#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 14, got 13
  *  test case 2 failed: expected 15, got 31
  *  test case 0 failed: expected 14, got 11
  */

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    if (value == 0 || value == UINT32_MAX) {
        return value;
    }

    return value | (value + UINT32_C(1));
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end = NULL;
    uintmax_t parsed;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 0);

    if (line == end || errno == ERANGE || parsed > UINT32_MAX) {
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n",
           set_rightmost_unset_bit((uint32_t)parsed));

    free(line);
    return EXIT_SUCCESS;
}