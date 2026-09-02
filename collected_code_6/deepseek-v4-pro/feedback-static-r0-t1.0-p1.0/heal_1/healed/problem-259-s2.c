#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef void (*TupleOperation)(int *result, const int *a, const int *b, size_t size);

static void maximize_elements(int *result, const int *a, const int *b, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        result[i] = (a[i] > b[i]) ? a[i] : b[i];
    }
}

static Tuple create_tuple(size_t size, const int *data) {
    Tuple tuple;
    tuple.elements = (int *)malloc(size * sizeof(int));
    if (tuple.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; ++i) {
        tuple.elements[i] = data[i];
    }
    tuple.size = size;
    return tuple;
}

static void destroy_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->elements != NULL) {
        free(tuple->elements);
        tuple->elements = NULL;
        tuple->size = 0;
    }
}

static Tuple maximize_tuples(const Tuple *a, const Tuple *b, TupleOperation operation) {
    if (a == NULL || b == NULL || a->elements == NULL || b->elements == NULL) {
        fprintf(stderr, "Invalid tuple input\n");
        exit(EXIT_FAILURE);
    }
    if (a->size != b->size) {
        fprintf(stderr, "Tuple sizes mismatch\n");
        exit(EXIT_FAILURE);
    }
    Tuple result;
    result.size = a->size;
    result.elements = (int *)malloc(result.size * sizeof(int));
    if (result.elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    operation(result.elements, a->elements, b->elements, result.size);
    return result;
}

static void print_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < tuple->size; ++i) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    int data1[] = {3, 7, 1, 9, 4};
    const int data2[] = {5, 2, 8, 6, 0};
    size_t size = sizeof(data1) / sizeof(data1[0]);

    Tuple tuple1 = create_tuple(size, data1);
    Tuple tuple2 = create_tuple(size, data2);

    Tuple max_tuple = maximize_tuples(&tuple1, &tuple2, maximize_elements);

    printf("Tuple 1: ");
    print_tuple(&tuple1);
    printf("Tuple 2: ");
    print_tuple(&tuple2);
    printf("Maximized tuple: ");
    print_tuple(&max_tuple);

    destroy_tuple(&tuple1);
    destroy_tuple(&tuple2);
    destroy_tuple(&max_tuple);

    return 0;
}