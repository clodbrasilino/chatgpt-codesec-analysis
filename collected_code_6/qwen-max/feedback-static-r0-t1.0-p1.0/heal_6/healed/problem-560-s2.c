#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

Tuple find_union(Tuple t1, Tuple t2) {
    size_t total_length = t1.length + t2.length;
    int *union_elements = (int *)malloc(total_length * sizeof(int));
    if (union_elements == NULL) {
        exit(EXIT_FAILURE);
    }
    memcpy(union_elements, t1.elements, t1.length * sizeof(int));
    memcpy(union_elements + t1.length, t2.elements, t2.length * sizeof(int));

    qsort(union_elements, total_length, sizeof(int), compare);

    size_t unique_count = 0;
    for (size_t i = 0; i < total_length; ++i) {
        if (i == 0 || union_elements[i] != union_elements[unique_count - 1]) {
            union_elements[unique_count++] = union_elements[i];
        }
    }

    int *new_union_elements = (int *)realloc(union_elements, unique_count * sizeof(int));
    if (new_union_elements == NULL) {
        free(union_elements);
        exit(EXIT_FAILURE);
    }

    Tuple result = { .elements = new_union_elements, .length = unique_count };
    return result;
}

void print_tuple(Tuple t) {
    for (size_t i = 0; i < t.length; ++i) {
        printf("%d ", t.elements[i]);
    }
    printf("\n");
}

void free_tuple(Tuple t) {
    free(t.elements);
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};

    Tuple t1 = { .elements = arr1, .length = sizeof(arr1) / sizeof(arr1[0]) };
    Tuple t2 = { .elements = arr2, .length = sizeof(arr2) / sizeof(arr2[0]) };

    Tuple union_result = find_union(t1, t2);

    printf("Union: ");
    print_tuple(union_result);

    free_tuple(union_result);
    return 0;
}