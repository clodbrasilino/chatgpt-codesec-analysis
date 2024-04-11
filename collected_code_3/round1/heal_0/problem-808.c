#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

bool containsK(Tuple tuples[], int size, int k) {
    for(int i = 0; i < size; i++) {
        if(tuples[i].x == k || tuples[i].y == k) {
            return true;
        }
    }
    return false;
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int k = 3;

    if(containsK(tuples, size, k)) {
        printf("The tuple contains %d\n", k);
    } else {
        printf("The tuple does not contain %d\n", k);
    }

    return 0;
}