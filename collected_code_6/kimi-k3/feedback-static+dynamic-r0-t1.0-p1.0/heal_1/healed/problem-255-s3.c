#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

void generate_combinations(int colors[], int n_colors, int combination[], int index, int r) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            printf("%d ", combination[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < n_colors; i++) {
        combination[index] = colors[i];
        generate_combinations(colors, n_colors, combination, index + 1, r);
    }
}

int main(void) {
    int colors[] = {1, 2, 3};
    int n_colors = 3;
    int r;

    printf("Enter the number of positions: ");
    if (scanf("%d", &r) != 1 || r <= 0 || r > 100 || (size_t)r > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *combination = malloc((size_t)r * sizeof(int));
    if (combination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    generate_combinations(colors, n_colors, combination, 0, r);

    free(combination);
    return EXIT_SUCCESS;
}