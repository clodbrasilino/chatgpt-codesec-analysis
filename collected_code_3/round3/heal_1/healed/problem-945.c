#include <stdio.h>
#include <stdlib.h>

typedef struct Set {
    int *elements;
    int size;
} Set;

Set convertToSet(int *tuple, int size) {
    Set set;
    set.elements = (int *)malloc(size * sizeof(int));
    if (!set.elements)
        return set;

    set.size = 0;
    for (int i = 0; i < size; i++) {
        int j;
        for (j = 0; j < set.size; j++)
            if (tuple[i] == set.elements[j])
                break;

        if (j == set.size) {
            set.elements[set.size] = tuple[i];
            set.size++;
        }
    }
    
    set.elements = realloc(set.elements, set.size * sizeof(int));

    return set;
}

int main() {
    int tuple[] = {1, 2, 3, 4, 2, 3, 1, 5};
    int size = sizeof(tuple) / sizeof(tuple[0]);

    Set set = convertToSet(tuple, size);
    if (!set.elements) {
        fprintf(stderr, "Failed to allocate memory for set.\n");
        return 1;
    }

    for (int i = 0; i < set.size; i++)
        printf("%d ", set.elements[i]);

    free(set.elements);

    return 0;
}