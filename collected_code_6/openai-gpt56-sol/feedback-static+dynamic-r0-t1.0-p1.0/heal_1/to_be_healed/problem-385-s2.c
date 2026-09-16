#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(size_t n, uint64_t *value)
{
    uint64_t a;
    uint64_t b;

    if (value == NULL) {
        return 0;
    }

    if (n == 0) {
        *value = 3;
        return 1;
    }

    if (n == 1) {
        *value = 0;
        return 1;
    }

    if (n == 2) {
        *value = 2;
        return 1;
    }

    if (!perrin(n - 2, &a) || !perrin(n - 3, &b)) {
        return 0;
    }

    if (UINT64_MAX - a < b) {
        return 0;
    }

    *value = a + b;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || input > SIZE_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!perrin((size_t)input, &result)) {
        fprintf(stderr, "Unable to calculate the Perrin number\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}