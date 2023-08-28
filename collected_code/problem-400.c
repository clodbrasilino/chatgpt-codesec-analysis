#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

int isUnique(Tuple* list, int n, Tuple tuple) {
    for (int i = 0; i < n; i++) {
        if (list[i].x == tuple.x && list[i].y == tuple.y) {
            return 0;
        }
    }
    return 1;
}

int findFrequency(Tuple* list, int n, Tuple tuple) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (list[i].x == tuple.x && list[i].y == tuple.y) {
            count++;
        }
    }
    return count;
}

void extractFrequency(Tuple* list, int n) {
    for (int i = 0; i < n; i++) {
        Tuple tuple = list[i];
        if (isUnique(list, i, tuple)) {
            int frequency = findFrequency(list, n, tuple);
            printf("(%d, %d) => %d\n", tuple.x, tuple.y, frequency);
        }
    }
}

int main() {
    Tuple list[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {7, 8}};
    int n = sizeof(list) / sizeof(list[0]);
    extractFrequency(list, n);
    return 0;
}