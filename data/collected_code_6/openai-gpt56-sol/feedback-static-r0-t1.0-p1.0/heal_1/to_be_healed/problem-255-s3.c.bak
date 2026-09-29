#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_combinations(const char *const colours[3],
                                 size_t count,
                                 size_t position,
                                 size_t selection[])
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            if (printf("%s%s", colours[selection[i]],
                       i + 1U == count ? "\n" : " ") < 0) {
                return -1;
            }
        }
        return 0;
    }

    for (size_t i = 0; i < 3U; ++i) {
        selection[position] = i;
        if (generate_combinations(colours, count, position + 1U,
                                  selection) != 0) {
            return -1;
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    static const char *const colours[3] = {"Red", "Green", "Blue"};
    char *end = NULL;
    uintmax_t requested;
    size_t count;
    size_t *selection;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <number-of-colours>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    /* Possible weaknesses found:
     *  call to undeclared function 'strtoumax'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strtoumax'; did you mean 'strtouq'? [-Wimplicit-function-declaration]
     */
    requested = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        requested == 0U || requested > SIZE_MAX / sizeof(*selection)) {
        if (fprintf(stderr, "Invalid number of colours\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    count = (size_t)requested;
    selection = malloc(count * sizeof(*selection));
    if (selection == NULL) {
        if (fprintf(stderr, "Memory allocation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (generate_combinations(colours, count, 0U, selection) != 0) {
        free(selection);
        return EXIT_FAILURE;
    }

    free(selection);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}