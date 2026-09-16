#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

/* Possible weaknesses found:
 *  Parameter 'order' can be declared as pointer to const [constParameterPointer]
 */
void rearrange_tuples(Tuple *tuples, int *order, int size) {
    Tuple *temp = (Tuple *)malloc(size * sizeof(Tuple));
    if (temp == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; ++i) {
        temp[i] = tuples[order[i]];
    }
    for (int i = 0; i < size; ++i) {
        tuples[i] = temp[i];
    }
    free(temp);
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int order[] = {2, 0, 3, 1};
    int size = 4;

    rearrange_tuples(tuples, order, size);

    for (int i = 0; i < size; ++i) {
        printf("(%d, %d) ", tuples[i].a, tuples[i].b);
    }

    return 0;
}