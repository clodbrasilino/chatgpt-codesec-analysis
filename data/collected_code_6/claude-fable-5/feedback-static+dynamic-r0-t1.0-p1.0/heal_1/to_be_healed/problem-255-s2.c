#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COLOURS 3
#define MAX_SELECTION 16

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
static const char *colours[NUM_COLOURS] = { "Red", "Green", "Blue" };

static void print_combination(const int *indices, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++) {
        printf("%s", colours[indices[i]]);
        if (i + 1U < count) {
            printf(" ");
        }
    }
    printf("\n");
}

static void generate_combinations(int *indices, size_t depth, size_t count, int start)
{
    int i;

    if (depth == count) {
        print_combination(indices, count);
        return;
    }

    for (i = start; i < NUM_COLOURS; i++) {
        indices[depth] = i;
        generate_combinations(indices, depth + 1U, count, i);
    }
}

static int choose_colours(size_t count)
{
    int *indices;

    if ((count == 0U) || (count > MAX_SELECTION)) {
        return -1;
    }

    indices = (int *)malloc(count * sizeof(int));
    if (indices == NULL) {
        return -1;
    }

    (void)memset(indices, 0, count * sizeof(int));
    generate_combinations(indices, 0U, count, 0);
    free(indices);
    indices = NULL;

    return 0;
}

int main(void)
{
    size_t count = 2U;
    int result;

    printf("Combinations with repetition choosing %zu colour(s) from %d colours:\n",
           count, NUM_COLOURS);

    result = choose_colours(count);
    if (result != 0) {
        fprintf(stderr, "Error: could not generate combinations.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}