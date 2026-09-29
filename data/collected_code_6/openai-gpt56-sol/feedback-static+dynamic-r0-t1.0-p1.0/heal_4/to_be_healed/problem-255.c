#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static const char *const colors[] = {
    "Red",
    "Green",
    "Blue"
};

#define COLOR_COUNT (sizeof colors / sizeof colors[0])

static int generate_combinations(size_t position,
                                 size_t count,
                                 size_t selection[static count])
{
    if (position == count) {
        for (size_t i = 0; i < count; ++i) {
            if (selection[i] >= COLOR_COUNT ||
                printf("%s%s",
                       colors[selection[i]],
                       i + 1U < count ? " " : "\n") < 0) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *const argv[const])
{
    char *end = NULL;
    unsigned long input;
    size_t count;
    size_t *selection;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number-of-colours>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoul(argv[1], &end, 10);

    if (errno != 0 ||
        end == argv[1] ||
        *end != '\0' ||
        input == 0UL ||
        input > SIZE_MAX ||
        (size_t)input > SIZE_MAX / sizeof *selection) {
        fputs("Invalid number of colours.\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)input;
    selection = malloc(count * sizeof *selection);

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