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
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        int value;
        if (sscanf(buffer, "%d", &value) == 1) {
            const char *newline = strchr(buffer, '\n');
            if (newline && newline - buffer < sizeof(buffer) - 1) {
                return value;
            }
        }
    }
    while ((getchar()) != '\n' && (getchar()) != EOF);
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