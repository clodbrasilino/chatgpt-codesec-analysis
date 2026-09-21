#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateCombinations(int *colors, int index, int k, int r) {
    if (index == k) {
        for (int i = 0; i < k; ++i) {
            printf("%d ", colors[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < r; ++i) {
        colors[index] = i + 1;
        generateCombinations(colors, index + 1, k, r);
    }
}

int readInt() {
    int value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        if (sscanf(buffer, "%d", &value) == 1) {
            /* Possible weaknesses found:
             *  Variable 'newline' can be declared as pointer to const [constVariablePointer]
             */
            char *newline = strchr(buffer, '\n');
            if (newline && newline - buffer < sizeof(buffer) - 1) {
                return value;
            }
        }
    }
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((getchar()) != '\n' && getchar() != EOF);
    return -1;
}

int main() {
    int k, r;

    printf("Enter the number of colors (max 3): ");
    r = readInt();
    if (r <= 0 || r > 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Enter the number of selections: ");
    k = readInt();
    if (k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    int *colors = (int *)malloc(k * sizeof(int));
    if (colors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    generateCombinations(colors, 0, k, r);

    free(colors);
    return 0;
}