#include <stdio.h>
#include <stdlib.h>

void generate_combinations(int *combination, int index, int n, int k, int num_colors) {
    int i;
    if (index == k) {
        for (i = 0; i < k; i++) {
            printf("%d", combination[i]);
            if (i < k - 1) {
                printf(" ");
            }
        }
        printf("\n");
        return;
    }
    for (i = 0; i < num_colors; i++) {
        combination[index] = i;
        generate_combinations(combination, index + 1, n, k, num_colors);
    }
}

int main(void) {
    int n = 3;
    int k;
    int *combination;
    
    printf("Enter number of positions to fill: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (k <= 0) {
        fprintf(stderr, "Number of positions must be positive\n");
        return EXIT_FAILURE;
    }
    
    combination = (int *)malloc((size_t)k * sizeof(int));
    if (combination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("All combinations with repetition:\n");
    generate_combinations(combination, 0, n, k, n);
    
    free(combination);
    combination = NULL;
    
    return EXIT_SUCCESS;
}