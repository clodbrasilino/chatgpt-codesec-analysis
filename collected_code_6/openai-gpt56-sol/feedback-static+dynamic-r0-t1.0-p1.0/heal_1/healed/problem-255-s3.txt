#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { COLOUR_COUNT = 3 };

static int generate_combinations(
    const char *const colours[static COLOUR_COUNT],
    size_t count,
    size_t position,
    size_t selection[static 1])
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            if (printf("%s%s",
                       colours[selection[i]],
                       i + 1 == count ? "\n" : " ") < 0) {
                return -1;
            }
        }
        return 0;
    }

    for (size_t i = 0; i < COLOUR_COUNT; ++i) {
        selection[position] = i;
        if (generate_combinations(
                colours, count, position + 1, selection) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    static const char *const colours[COLOUR_COUNT] = {
        "Red",
        "Green",
        "Blue"
    };

    char *end = NULL;
    uintmax_t requested;
    size_t count;
    size_t *selection;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number-of-colours>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    requested = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        requested == 0 ||
        requested > SIZE_MAX ||
        requested > SIZE_MAX / sizeof(*selection)) {
        fprintf(stderr, "Invalid number of colours\n");
        return EXIT_FAILURE;
    }

    count = (size_t)requested;
    selection = malloc(count * sizeof(*selection));

    if (selection == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (generate_combinations(colours, count, 0, selection) != 0) {
        free(selection);
        return EXIT_FAILURE;
    }

    free(selection);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}