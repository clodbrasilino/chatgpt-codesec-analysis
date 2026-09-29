#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* elements;
    int size;
} Tuple;

typedef struct {
    Tuple* tuples;
    int size;
} TupleList;

bool contains(const int* array, int size, int element) {
    if (array == NULL) return false;
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
}

Tuple intersection(TupleList list) {
    Tuple result = {NULL, 0};
    if (list.size == 0 || list.tuples == NULL) {
        return result;
    }

    int capacity = list.tuples[0].size;
    result.elements = (int*)malloc(capacity * sizeof(int));
    if (result.elements == NULL) {
        return result;
    }

    for (int i = 0; i < list.tuples[0].size; i++) {
        int current_element = list.tuples[0].elements[i];
        bool found_in_all = true;

        for (int j = 1; j < list.size; j++) {
            if (!contains(list.tuples[j].elements, list.tuples[j].size, current_element)) {
                found_in_all = false;
                break;
            }
        }

        if (found_in_all && !contains(result.elements, result.size, current_element)) {
            result.elements[result.size++] = current_element;
        }
    }

    int* temp = (int*)realloc(result.elements, result.size * sizeof(int));
    if (temp != NULL || result.size == 0) {
        result.elements = temp;
    }

    return result;
}

void free_tuple(Tuple* t) {
    if (t != NULL && t->elements != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 1};
    int arr3[] = {5, 1, 8, 9, 4};

    Tuple t1 = {arr1, 5};
    Tuple t2 = {arr2, 5};
    Tuple t3 = {arr3, 5};

    Tuple tuples_arr[] = {t1, t2, t3};
    TupleList list = {tuples_arr, 3};

    Tuple inter = intersection(list);

    for (int i = 0; i < inter.size; i++) {
        printf("%d ", inter.elements[i]);
    }
    printf("\n");

    free_tuple(&inter);

    return 0;
}