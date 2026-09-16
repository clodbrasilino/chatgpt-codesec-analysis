#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t count_hex_numbers(uint64_t start, uint64_t end)
{
    return end - start + UINT64_C(1);
}

static int parse_uint64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 0);

    if (errno == ERANGE || end == text || *end != '\0' || parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

int main(int argc, const char *const argv[])
{
    uint64_t start;
    uint64_t end;
    uint64_t count;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <start> <end>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uint64(argv[1], &start) || !parse_uint64(argv[2], &end)) {
        fprintf(stderr, "Invalid range value\n");
        return EXIT_FAILURE;
    }

    if (start > end) {
        fprintf(stderr, "Start must not exceed end\n");
        return EXIT_FAILURE;
    }

    count = count_hex_numbers(start, end);

    if (count == UINT64_C(0)) {
        puts("Count: 18446744073709551616");
    } else {
        printf("Count: %" PRIu64 "\n", count);
    }

    return EXIT_SUCCESS;
}