#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_combinations(const char *const colours[],
                                 size_t colour_count,
                                 size_t count,
                                 size_t position,
                                 size_t selection[])
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            if (selection[i] >= colour_count ||
                printf("%s%s",
                       colours[selection[i]],
                       i + 1U == count ? "\n" : " ") < 0) {
                return -1;
            }
        }
        return 0;
    }

    for (size_t i = 0; i < colour_count; ++i) {
        selection[position] = i;
        if (generate_combinations(colours, colour_count, count,
                                  position + 1U, selection) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    static const char *const colours[] = {"Red", "Green", "Blue"};
    const size_t colour_count = sizeof(colours) / sizeof(colours[0]);
    char *end = NULL;
    uintmax_t requested;
    size_t count;
    size_t *selection;

    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <number-of-colours>\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    requested = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
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

    if (generate_combinations(colours, colour_count, count, 0, selection) != 0) {
        free(selection);
        return EXIT_FAILURE;
    }

    free(selection);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}