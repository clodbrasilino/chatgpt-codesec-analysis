#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_hex_numbers(uint64_t start, uint64_t end, uint64_t *count)
{
    if (count == NULL || start > end ||
        (start == UINT64_C(0) && end == UINT64_MAX)) {
        return -1;
    }

    *count = end - start + UINT64_C(1);
    return 0;
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 0);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    return 0;
}

int main(int argc, const char *const argv[])
{
    uint64_t start;
    uint64_t end;
    uint64_t count;

    if (argc != 3) {
        (void)fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_uint64(argv[1], &start) != 0 ||
        parse_uint64(argv[2], &end) != 0) {
        (void)fprintf(stderr, "Invalid range value\n");
        return EXIT_FAILURE;
    }

    if (count_hex_numbers(start, end, &count) != 0) {
        (void)fprintf(stderr, "Invalid or unrepresentable range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}