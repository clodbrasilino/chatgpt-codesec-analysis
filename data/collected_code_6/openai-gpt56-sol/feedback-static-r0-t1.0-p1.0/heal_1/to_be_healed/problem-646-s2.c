#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

static int count_cubes(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t count;

    if (result == NULL || k == 0 || k > n) {
        return -1;
    }

    count = n / k;

    if (count != 0 && count > UINT64_MAX / count) {
        return -1;
    }

    *result = count * count;

    if (count != 0 && *result > UINT64_MAX / count) {
        return -1;
    }

    *result *= count;
    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    uint64_t n;
    uint64_t k;
    uint64_t result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_uint64(argv[1], &n) != 0 ||
        parse_uint64(argv[2], &k) != 0 ||
        count_cubes(n, k, &result) != 0) {
        fprintf(stderr, "Invalid input or arithmetic overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}