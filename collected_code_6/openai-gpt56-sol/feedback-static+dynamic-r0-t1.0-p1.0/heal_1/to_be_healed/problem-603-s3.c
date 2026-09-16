#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t get_lucid_number(uint64_t n)
{
    if (n == 0U) {
        return 0U;
    }

    uint64_t power = 1U;

    while (power <= n / 10U) {
        power *= 10U;
    }

    return n - (n % power);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = get_lucid_number((uint64_t)input);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}