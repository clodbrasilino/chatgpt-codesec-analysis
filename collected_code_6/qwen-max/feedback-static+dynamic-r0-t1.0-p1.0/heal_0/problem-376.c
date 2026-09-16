#include <stdio.h>
#include <stdlib.h>

#define CUSTOM_VALUE -1

typedef struct {
    int *elements;
    size_t length;
} Tuple;

Tuple create_tuple(int arr[], size_t length) {
    Tuple t;
    t.elements = (int *)malloc(length * sizeof(int));
    if (t.elements == NULL) {
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < length; i++) {
        t.elements[i] = arr[i];
    }
    t.length = length;
    return t;
}

void print_tuple(const Tuple *t) {
    for (size_t i = 0; i < t->length; i++) {
        printf("%d ", t->elements[i]);
    }
    printf("\n");
}

int count_occurrences(const Tuple *t, int value) {
    int count = 0;
    for (size_t i = 0; i < t->length; i++) {
        if (t->elements[i] == value) {
            count++;
        }
    }
    return count;
}

void remove_duplicates(Tuple *t) {
    for (size_t i = 0; i < t->length; i++) {
        if (count_occurrences(t, t->elements[i]) > 1) {
            t->elements[i] = CUSTOM_VALUE;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 5, 3, 6};
    size_t length = sizeof(arr) / sizeof(arr[0]);

    Tuple t = create_tuple(arr, length);

    printf("Original tuple: ");
    print_tuple(&t);

    remove_duplicates(&t);

    printf("Tuple after removing duplicates: ");
    print_tuple(&t);

    free(t.elements);
    t.elements = NULL;

    return 0;
}