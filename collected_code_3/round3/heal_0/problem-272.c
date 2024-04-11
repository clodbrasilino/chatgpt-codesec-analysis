#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    int a;
    int b;
} Tuple;

Tuple* create_tuple(int a, int b) {
    Tuple* new_tuple = (Tuple*)malloc(sizeof(Tuple));
    new_tuple->a = a;
    new_tuple->b = b;
    return new_tuple;
}

int extract_rear(Tuple** tuples, int size) {
    return tuples[size - 1]->b;
}

int main() {
    int size = 5;
    Tuple** tuples = (Tuple**)malloc(size * sizeof(Tuple*));
    for(int i = 0; i < size; i++) {
        tuples[i] = create_tuple(i, i * 2);
    }
    int rear = extract_rear(tuples, size);
    printf("Rear element: %d\n", rear);
    for(int i = 0; i < size; i++) {
        free(tuples[i]);
    }
    free(tuples);
    return 0;
}