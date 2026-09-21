#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  */

static bool is_woodall(uint64_t number)
{
    uint64_t power_of_two = 2;

    for (uint64_t n = 1; n <= 63; ++n) {
        if (n > UINT64_MAX / power_of_two) {
            return false;
        }

        uint64_t product = n * power_of_two;

        if (product == number + 1) {
            return true;
        }

        if (product > number + 1 || power_of_two > UINT64_MAX / 2) {
            return false;
        }

        power_of_two *= 2;
    }

    return false;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;

    if (getline(&input, &capacity, stdin) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", is_woodall((uint64_t)value) ? "True" : "False");

    free(input);
    return EXIT_SUCCESS;
}