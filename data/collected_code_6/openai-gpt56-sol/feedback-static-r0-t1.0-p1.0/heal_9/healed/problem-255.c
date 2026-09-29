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
                                 size_t selection[static 1])
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            size_t color = selection[i];

            if (color >= COLOR_COUNT ||
                fputs(colors[color], stdout) == EOF ||
                fputc(i + 1U < count ? ' ' : '\n', stdout) == EOF) {
                return -1;
            }
        }

        return 0;
    }

    if (position > count) {
        return -1;
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
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <number-of-colours>\n", program);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long input = strtoul(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        end == NULL ||
        *end != '\0' ||
        input == 0UL ||
        input > SIZE_MAX ||
        (size_t)input > SIZE_MAX / sizeof(size_t)) {
        fputs("Invalid number of colours.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)input;
    size_t *selection = malloc(count * sizeof(*selection));

    if (selection == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    int result = generate_combinations(0U, count, selection);
    free(selection);

    if (result != 0 || fflush(stdout) == EOF) {
        fputs("Output error.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}