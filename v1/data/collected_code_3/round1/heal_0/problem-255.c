#include <stdio.h>

void printCombinationsRepetition(char data[], int start, int end, int index, int r) {
    static char color[] = {'R', 'G', 'B'};
    if (index == r) {
        for (int j = 0; j < r; j++)
            printf("%c ", data[j]);
        printf("\n");
        return;
    }
    for (int i = start; i <= end && end - i + 1 >= r - index; i++) {
        data[index] = color[i];
        printCombinationsRepetition(data, i, end, index + 1, r);
    }
}

void combinationsRepetition(int n, int r) {
    char data[r];
    printCombinationsRepetition(data, 0, n - 1, 0, r);
}

int main() {
    int n = 3;
    int r = 2;
    combinationsRepetition(n, r);
    return 0;
}