#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int c;
} Tuple;

int maxInColumn(Tuple *tuples, size_t length, int col) {
    if (length == 0 || col < 0 || col > 2) return -1;
    
    int max = tuples[0].a;
    for (size_t i = 1; i < length; ++i) {
        int value = 0;
        switch (col) {
            case 0: value = tuples[i].a; break;
            case 1: value = tuples[i].b; break;
            case 2: value = tuples[i].c; break;
        }
        if (value > max) max = value;
    }
    return max;
}

int main() {
    Tuple tuples[] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    size_t length = sizeof(tuples) / sizeof(tuples[0]);
    int col = 1;
    
    int result = maxInColumn(tuples, length, col);
    printf("Max in column %d: %d\n", col, result);

    return 0;
}