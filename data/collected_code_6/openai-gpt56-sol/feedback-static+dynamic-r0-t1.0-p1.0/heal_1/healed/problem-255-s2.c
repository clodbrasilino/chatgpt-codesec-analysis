#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { COLOUR_COUNT = 3 };

static int generate_combinations(
    const char *const colours[static COLOUR_COUNT],
    size_t selection[static COLOUR_COUNT],
    size_t colour_index,
    size_t remaining)
{
    if (colour_index == COLOUR_COUNT - 1) {
        selection[colour_index] = remaining;

        if (printf("%s: %zu, %s: %zu, %s: %zu\n",
                   colours[0], selection[0],
                   colours[1], selection[1],
                   colours[2], selection[2]) < 0) {
            return -1;
        }

        return 0;
    }

    for (size_t count = 0;; ++count) {
        selection[colour_index] = count;

        if (generate_combinations(colours, selection, colour_index + 1,
                                  remaining - count) != 0) {
            return -1;
        }

        if (count == remaining) {
            break;
        }
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    static const char *const colours[COLOUR_COUNT] = {
        "Red",
        "Green",
        "Blue"
    };
    size_t selection[COLOUR_COUNT] = {0};
    char *end = NULL;
    unsigned long long parsed_count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER_OF_COLOURS\n", argv[0]);
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

    if (generate_combinations(colours, selection, 0,
                              (size_t)parsed_count) != 0) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}