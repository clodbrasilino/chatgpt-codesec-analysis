#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NUM_COLOURS 3
#define MAX_COUNT 64

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static const char *colours[NUM_COLOURS] = { "Red", "Green", "Blue" };

static void print_combination(const int *indices, size_t count)
{
    size_t i;

    if (indices == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        if (indices[i] < 0 || indices[i] >= NUM_COLOURS) {
            return;
        }
        printf("%s", colours[indices[i]]);
        if (i + 1 < count) {
            printf(" ");
        }
    }
    printf("\n");
}

static void generate_combinations(int *indices, size_t depth, size_t count, int start)
{
    int i;

    if (indices == NULL || depth > count) {
        return;
    }

    if (depth == count) {
        print_combination(indices, count);
        return;
    }

    for (i = start; i < NUM_COLOURS; i++) {
        indices[depth] = i;
        generate_combinations(indices, depth + 1, count, i);
    }
}

static int choose_colours(size_t count)
{
    int *indices;

    if (count == 0 || count > MAX_COUNT) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*indices)) {
        return -1;
    }

    indices = calloc(count, sizeof(*indices));
    if (indices == NULL) {
        return -1;
    }

    generate_combinations(indices, 0, count, 0);
    free(indices);
    return 0;
}

int main(void)
{
    size_t count = 2;

    printf("Combinations with repetition choosing %zu colours from %d:\n",
           count, NUM_COLOURS);

    if (choose_colours(count) != 0) {
        fprintf(stderr, "Failed to generate combinations\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}