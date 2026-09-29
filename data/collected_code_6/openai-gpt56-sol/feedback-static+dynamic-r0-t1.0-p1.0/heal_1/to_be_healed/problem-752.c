#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int jacobsthal(uint32_t n, uint64_t *result)
{
    uint64_t previous = 0U;
    uint64_t current = 1U;

    if (result == NULL) {
        return -1;
    }

    if (n == 0U) {
        *result = previous;
        return 0;
    }

    for (uint32_t i = 1U; i < n; ++i) {
        if (previous > (UINT64_MAX - current) / 2U) {
            return -1;
        }

        const uint64_t next = current + (2U * previous);
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (jacobsthal((uint32_t)input, &result) != 0) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}