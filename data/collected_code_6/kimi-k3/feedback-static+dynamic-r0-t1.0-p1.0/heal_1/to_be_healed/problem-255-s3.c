#include <stdio.h>
#include <stdlib.h>

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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:11487,execs:486,op:havoc,rep:15; likely memory-safety defect
  */

int main(void) {
    int colors[] = {1, 2, 3};
    int n_colors = 3;
    int r;

    printf("Enter the number of positions: ");
    if (scanf("%d", &r) != 1 || r <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *combination = malloc(r * sizeof(int));
    if (combination == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    generate_combinations(colors, n_colors, combination, 0, r);

    free(combination);
    return EXIT_SUCCESS;
}