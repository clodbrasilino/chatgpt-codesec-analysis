#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int perfect_square_root(unsigned long long number,
                               unsigned long long *root)
{
    unsigned long long low = 0;
    unsigned long long high = number;
    unsigned long long result = 0;

    if (root == NULL) {
        return 0;
    }

    while (low <= high) {
        unsigned long long mid = low + (high - low) / 2;

        if (mid != 0 && mid > number / mid) {
            high = mid - 1;
        } else {
            unsigned long long square = mid * mid;

            if (square == number) {
                *root = mid;
                return 1;
            }

            result = mid;
            low = mid + 1;
        }
    }

    (void)result;
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long number;
    unsigned long long root;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <non-negative perfect square>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '-') {
        fprintf(stderr, "Input must be non-negative.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    number = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!perfect_square_root(number, &root)) {
        fprintf(stderr, "%llu is not a perfect square.\n", number);
        return EXIT_FAILURE;
    }

    printf("%llu\n", root);
    return EXIT_SUCCESS;
}