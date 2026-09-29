#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int differ_by_one_bit(unsigned long long first, unsigned long long second)
{
    const unsigned long long difference = first ^ second;

    return difference != 0ULL &&
           (difference & (difference - 1ULL)) == 0ULL;
}

static int parse_number(const char *text, unsigned long long *value)
{
    char *end = NULL;
    unsigned long long result;

    errno = 0;
    result = strtoull(text, &end, 0);

    if (errno == ERANGE || end == text || *end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

int main(int argc, char *const argv[])
{
    unsigned long long first;
    unsigned long long second;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number1> <number2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_number(argv[1], &first) ||
        !parse_number(argv[2], &second)) {
        fprintf(stderr, "Invalid unsigned integer input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", differ_by_one_bit(first, second) ? "Yes" : "No");

    return EXIT_SUCCESS;
}