#include <stdio.h>
#include <stdlib.h>

void generate_combinations(int *current_combination, int start, int index, int k, int *colors, int num_colors) {
    if (index == k) {
        for (int i = 0; i < k; i++) {
            printf("%d ", current_combination[i]);
        }
        printf("\n");
        return;
    }

    for (int i = start; i < num_colors; i++) {
        current_combination[index] = colors[i];
        generate_combinations(current_combination, i, index + 1, k, colors, num_colors);
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int colors[] = {1, 2, 3};
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    int k;
    int *current_combination = NULL;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    k = atoi(argv[1]);

    if (k <= 0) {
        fprintf(stderr, "Invalid number of colors to choose.\n");
        return EXIT_FAILURE;
    }

    current_combination = (int *)malloc(k * sizeof(int));
    if (current_combination == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    generate_combinations(current_combination, 0, 0, k, colors, num_colors);

    free(current_combination);
    current_combination = NULL;

    return EXIT_SUCCESS;
}