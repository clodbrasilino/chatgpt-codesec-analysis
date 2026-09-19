#include <stdio.h>
#include <stdlib.h>

void generateCombinations(int n, int *colors, int index, int k, int r) {
    if (index == k) {
        for (int i = 0; i < k; ++i) {
            printf("%d ", colors[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < r; ++i) {
        colors[index] = i + 1;
        generateCombinations(n, colors, index + 1, k, r);
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000000,time:4885,execs:1155,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     *  Unused variable: n [unusedVariable]
     */
    int n, k, r;

    printf("Enter the number of colors (max 3): ");
    scanf("%d", &r);

    printf("Enter the number of selections: ");
    scanf("%d", &k);

    if (r > 3 || r <= 0 || k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int *colors = (int *)malloc(k * sizeof(int));
    if (colors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    generateCombinations(r, colors, 0, k, r);

    free(colors);
    return 0;
}