#include <stdio.h>

void generateCombinations(char *colours, int r, char *data, int start, int end, int index) {
    int i, j;
    if (index == r) {
        for (j = 0; j < r; j++)
            printf("%c ", data[j]);
        printf("\n");
        return;
    }

    for (i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = colours[i];
        generateCombinations(colours, r, data, i, end, index + 1);
    }
}

void getCombinations(char *colours, int n, int r) {
    char data[r];
    generateCombinations(colours, r, data, 0, n - 1, 0);
}

int main() {
    char colours[] = {'R', 'G', 'B'};
    int r = 2;
    int n = sizeof(colours) / sizeof(colours[0]);
    getCombinations(colours, n, r);
    return 0;
}