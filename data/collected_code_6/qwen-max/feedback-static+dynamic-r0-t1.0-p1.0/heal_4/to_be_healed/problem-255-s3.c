#include <stdio.h>
#include <stdlib.h>

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
    if (scanf("%d", &value) != 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (getchar() != '\n');
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    char c = getchar();
    if (c != '\n') {
        /* Possible weaknesses found:
         *  Storing getchar() return value in char variable and then comparing with EOF. [checkCastIntToCharAndBack]
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (c != '\n' && c != EOF) c = getchar();
        return -1;
    }
    return value;
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