#include <stdio.h>

struct tuple {
    int x;
    int y;
    int z;
};

void trimTuples(struct tuple tuples[], int size, int k) {
    for (int i = 0; i < size; i++) {
        tuples[i].x -= k;
        tuples[i].y -= k;
        tuples[i].z -= k;
    }
}

int main() {
    struct tuple tuples[] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int k = 2;

    trimTuples(tuples, size, k);

    for (int i = 0; i < size; i++) {
        printf("(%d, %d, %d)\n", tuples[i].x, tuples[i].y, tuples[i].z);
    }

    return 0;
}