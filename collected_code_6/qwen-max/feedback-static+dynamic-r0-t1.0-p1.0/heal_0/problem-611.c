#include <stdio.h>
#include <limits.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

int findMaxInColumn(Tuple *tuples, int size, int column) {
    int max = INT_MIN;
    for (int i = 0; i < size; i++) {
        int value;
        switch (column) {
            case 0: value = tuples[i].a; break;
            case 1: value = tuples[i].b; break;
            case 2: value = tuples[i].c; break;
            default: return -1; // Invalid column
        }
        if (value > max) {
            max = value;
        }
    }
    return max;
}

int main() {
    Tuple tuples[] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int column = 1;
    int max = findMaxInColumn(tuples, size, column);
    printf("Maximum in column %d is %d\n", column, max);
    return 0;
}