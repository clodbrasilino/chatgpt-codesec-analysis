#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { COLOR_COUNT = 3 };

static const char *const colors[] = {
    "Red",
    "Green",
    "Blue"
};

static int generate_combinations(size_t position, size_t count,
                                 size_t *selection)
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            if (selection[i] >= COLOR_COUNT) {
                return -1;
            }

            if (fputs(colors[selection[i]], stdout) == EOF ||
                fputc(i + 1U < count ? ' ' : '\n', stdout) == EOF) {
                return -1;
            }
        }

        return 0;
    }

    for (size_t color = 0; color < COLOR_COUNT; ++color) {
        selection[position] = color;

        if (generate_combinations(position + 1U, count, selection) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *end;
    unsigned long input;
    size_t count;
    size_t *selection;

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <number-of-colours>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        input == 0UL ||
        input > SIZE_MAX ||
        (size_t)input > SIZE_MAX / sizeof(*selection)) {
        fputs("Invalid number of colours.\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)input;
    selection = malloc(count * sizeof(*selection));

    if (selection == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (generate_combinations(0U, count, selection) != 0) {
        free(selection);
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    free(selection);

    if (fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}