#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
    int *elements;
    int size;
} Set;

Set convertToSet(int *tuple, int size) {
    Set set;
    set.elements = (int *)malloc(size * sizeof(int));
    set.size = 0;

    for (int i = 0; i < size; i++) {
        int j;
        for (j = 0; j < i; j++)
            if (tuple[i] == tuple[j])
                break;

        if (i == j) {
            set.elements[set.size] = tuple[i];
            set.size++;
        }
    }

    return set;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 2, 3, 1, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    Set set = convertToSet(tuple, size);

    for (int i = 0; i < set.size; i++)
        printf("%d ", set.elements[i]);

    free(set.elements);

    return 0;
}