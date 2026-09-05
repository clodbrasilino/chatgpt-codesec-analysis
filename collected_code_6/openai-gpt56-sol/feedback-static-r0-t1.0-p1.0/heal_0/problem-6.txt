#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static int differ_by_one_bit(uintmax_t first, uintmax_t second)
{
    const uintmax_t difference = first ^ second;

    return difference != 0 && (difference & (difference - 1)) == 0;
}

static int parse_uintmax(const char *text, uintmax_t *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    const uintmax_t parsed = strtoumax(text, &end, 0);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, char *argv[])
{
    uintmax_t first = 0;
    uintmax_t second = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <first-number> <second-number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_uintmax(argv[1], &first) || !parse_uintmax(argv[2], &second)) {
        fprintf(stderr, "Both arguments must be valid nonnegative integers.\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", differ_by_one_bit(first, second) ? "Yes" : "No");
    return EXIT_SUCCESS;
}