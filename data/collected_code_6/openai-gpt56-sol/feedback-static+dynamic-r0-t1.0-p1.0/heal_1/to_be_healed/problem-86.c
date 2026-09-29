#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int centered_hexagonal_number(uint64_t n, uint64_t *result)
{
    if (n == 0 || result == NULL) {
        return 0;
    }

    uint64_t a = n;
    uint64_t b = n - 1;

    if ((a & 1U) == 0U) {
        a /= 2;
    } else {
        b /= 2;
    }

    if (a != 0 && b > (UINT64_MAX - 1) / a) {
        return 0;
    }

    *result = 6 * (a * b) + 1;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        input == 0 || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = 0;

    if (!centered_hexagonal_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}