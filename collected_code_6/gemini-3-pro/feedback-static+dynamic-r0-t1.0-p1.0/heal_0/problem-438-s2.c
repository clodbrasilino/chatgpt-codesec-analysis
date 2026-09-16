#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

int count_bidirectional_pairs(Tuple* tuples, size_t size) {
    if (tuples == NULL || size == 0) {
        return 0;
    }

    int count = 0;
    bool* visited = (bool*)calloc(size, sizeof(bool));
    if (visited == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        if (visited[i]) {
            continue;
        }

        for (size_t j = i + 1; j < size; j++) {
            if (!visited[j] && tuples[i].x == tuples[j].y && tuples[i].y == tuples[j].x) {
                count++;
                visited[i] = true;
                visited[j] = true;
                break;
            }
        }
    }

    free(visited);
    return count;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {2, 1},
        {3, 4},
        {5, 6},
        {6, 5},
        {1, 2}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);
    
    int result = count_bidirectional_pairs(tuples, size);
    if (result != -1) {
        printf("Count: %d\n", result);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}