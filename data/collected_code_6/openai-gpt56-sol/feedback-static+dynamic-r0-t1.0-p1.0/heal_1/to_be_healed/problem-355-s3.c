#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 8, got 4
  */

static unsigned long long count_rectangles(unsigned int radius)
{
    unsigned long long count = 0;
    unsigned long long r_squared =
        (unsigned long long)radius * (unsigned long long)radius;

    for (unsigned int width = 1; width <= radius; ++width) {
        for (unsigned int height = 1; height <= radius; ++height) {
            unsigned long long diagonal_squared =
                (unsigned long long)width * width +
                (unsigned long long)height * height;

            if (diagonal_squared <= 4ULL * r_squared) {
                ++count;
            }
        }
    }

    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long input;
    unsigned int radius;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <radius>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        input == 0 || input > 46340UL) {
        fprintf(stderr, "Invalid radius\n");
        return EXIT_FAILURE;
    }

    radius = (unsigned int)input;
    printf("%llu\n", count_rectangles(radius));

    return EXIT_SUCCESS;
}