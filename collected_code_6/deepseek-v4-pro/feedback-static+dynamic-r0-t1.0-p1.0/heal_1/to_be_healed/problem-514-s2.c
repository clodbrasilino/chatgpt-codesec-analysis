#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

int sum_tuple(const Tuple *t) {
    if (!t || !t->elements) return 0;
    int total = 0;
    for (int i = 0; i < t->size; i++) {
        total += t->elements[i];
    }
    return total;
}

int sum_tuple_list(const Tuple *tuples, int count) {
    if (!tuples || count <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += sum_tuple(&tuples[i]);
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
Tuple create_tuple(int *arr, int size) {
    Tuple t;
    t.size = size;
    t.elements = malloc(sizeof(int) * size);
    if (t.elements) {
        for (int i = 0; i < size; i++) {
            t.elements[i] = arr[i];
        }
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t && t->elements) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {6, 7, 8, 9};

    Tuple tuples[3];
    tuples[0] = create_tuple(arr1, 3);
    tuples[1] = create_tuple(arr2, 2);
    tuples[2] = create_tuple(arr3, 4);

    int total = sum_tuple_list(tuples, 3);
    printf("%d\n", total);

    for (int i = 0; i < 3; i++) {
        free_tuple(&tuples[i]);
    }

    return 0;
}