#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COLOURS 3
#define MAX_SELECTION 32

static const char *colours[NUM_COLOURS] = { "Red", "Green", "Blue" };

static void print_combination(const int *indices, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (i > 0) {
            if (printf(" ") < 0) {
                exit(EXIT_FAILURE);
            }
        }
        if (printf("%s", colours[indices[i]]) < 0) {
            exit(EXIT_FAILURE);
        }
    }
    if (printf("\n") < 0) {
        exit(EXIT_FAILURE);
    }
}

static void generate_combinations(int *indices, size_t count, size_t position, int start)
{
    int c;

    if (position == count) {
        print_combination(indices, count);
        return;
    }

    for (c = start; c < NUM_COLOURS; c++) {
        indices[position] = c;
        generate_combinations(indices, count, position + 1U, c);
    }
}

static int choose_colours(size_t count)
{
    int *indices;

    if (count == 0U || count > MAX_SELECTION) {
        return -1;
    }

    indices = (int *)malloc(count * sizeof(int));
    if (indices == NULL) {
        return -1;
    }

    memset(indices, 0, count * sizeof(int));
    generate_combinations(indices, count, 0U, 0);

    free(indices);
    indices = NULL;

    return 0;
}

int main(void)
{
    size_t count = 2U;

    if (printf("Combinations with repetition choosing %zu colour(s) from %d colours:\n",
               count, NUM_COLOURS) < 0) {
        return EXIT_FAILURE;
    }

    if (choose_colours(count) != 0) {
        if (fprintf(stderr, "Failed to generate combinations.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}