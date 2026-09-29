#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int integer_square_root(unsigned long long number,
                               unsigned long long *root)
{
    unsigned long long low = 0;
    unsigned long long high = number < (unsigned long long)UINT_MAX
                                  ? number
                                  : (unsigned long long)UINT_MAX;

    if (root == NULL) {
        return 0;
    }

    while (low <= high) {
        unsigned long long middle = low + (high - low) / 2;

        if (middle != 0 && middle > number / middle) {
            high = middle - 1;
        } else {
            unsigned long long square = middle * middle;

            if (square == number) {
                *root = middle;
                return 1;
            }

            low = middle + 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long number;
    unsigned long long root;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <perfect-square>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Invalid non-negative integer.\n");
        return EXIT_FAILURE;
    }

    if (!integer_square_root(number, &root)) {
        fprintf(stderr, "%llu is not a perfect square.\n", number);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", root) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}