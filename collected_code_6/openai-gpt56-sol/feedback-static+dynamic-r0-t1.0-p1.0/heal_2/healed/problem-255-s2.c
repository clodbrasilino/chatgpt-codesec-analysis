#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { COLOUR_COUNT = 3 };

static int generate_combinations(
    const char *const *colours,
    size_t colour_count,
    size_t *selection,
    size_t selection_count,
    size_t colour_index,
    size_t remaining)
{
    if (colours == NULL ||
        selection == NULL ||
        colour_count == 0 ||
        colour_count != selection_count ||
        colour_index >= colour_count) {
        return -1;
    }

    if (colour_index == colour_count - 1) {
        selection[colour_index] = remaining;

        for (size_t i = 0; i < colour_count; ++i) {
            if (printf("%s: %zu%s",
                       colours[i],
                       selection[i],
                       i + 1 == colour_count ? "\n" : ", ") < 0) {
                return -1;
            }
        }

        return 0;
    }

    for (size_t count = 0; count <= remaining; ++count) {
        selection[colour_index] = count;

        if (generate_combinations(colours,
                                  colour_count,
                                  selection,
                                  selection_count,
                                  colour_index + 1,
                                  remaining - count) != 0) {
            return -1;
        }

        if (count == remaining) {
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    static const char *const colours[] = {
        "Red",
        "Green",
        "Blue"
    };
    size_t selection[COLOUR_COUNT] = {0};
    char *end = NULL;
    unsigned long long parsed_count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER_OF_COLOURS\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_count = strtoull(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed_count > SIZE_MAX) {
        fprintf(stderr, "Invalid number of colours: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (generate_combinations(colours,
                              COLOUR_COUNT,
                              selection,
                              COLOUR_COUNT,
                              0,
                              (size_t)parsed_count) != 0) {
        fprintf(stderr, "Failed to generate or write output\n");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}