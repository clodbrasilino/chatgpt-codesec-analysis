#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

void find_symmetric_pairs(Tuple* tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return;
    }

    int* visited = (int*)calloc(size, sizeof(int));
    if (visited == NULL) {
        return;
    }

    for (int i = 0; i < size; i++) {
        if (visited[i]) {
            continue;
        }

        for (int j = i + 1; j < size; j++) {
            if (!visited[j] && tuples[i].first == tuples[j].second && tuples[i].second == tuples[j].first) {
                printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
                visited[i] = 1;
                visited[j] = 1;
                break;
            }
        }
    }

    free(visited);
}

int main(void) {
    Tuple tuples[] = {
        {11, 20},
        {30, 40},
        {5, 10},
        {40, 30},
        {10, 5},
        {20, 11},
        {15, 25}
    };
    int size = sizeof(tuples) / sizeof(tuples[0]);

    find_symmetric_pairs(tuples, size);

    return 0;
}