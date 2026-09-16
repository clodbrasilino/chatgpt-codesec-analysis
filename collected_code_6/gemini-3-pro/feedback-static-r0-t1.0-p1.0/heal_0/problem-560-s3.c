#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct Tuple* find_union(const struct Tuple *tuple1, const struct Tuple *tuple2) {
    if (!tuple1 || !tuple2) {
        return NULL;
    }

    struct Tuple *result = (struct Tuple *)malloc(sizeof(struct Tuple));
    if (!result) {
        return NULL;
    }

    size_t max_size = tuple1->size + tuple2->size;
    result->elements = (int *)malloc(max_size * sizeof(int));
    if (!result->elements) {
        free(result);
        return NULL;
    }

    size_t current_size = 0;

    for (size_t i = 0; i < tuple1->size; ++i) {
        int is_duplicate = 0;
        for (size_t k = 0; k < current_size; ++k) {
            if (result->elements[k] == tuple1->elements[i]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            result->elements[current_size++] = tuple1->elements[i];
        }
    }

    for (size_t j = 0; j < tuple2->size; ++j) {
        int is_duplicate = 0;
        for (size_t k = 0; k < current_size; ++k) {
            if (result->elements[k] == tuple2->elements[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            result->elements[current_size++] = tuple2->elements[j];
        }
    }

    result->size = current_size;

    int *temp = (int *)realloc(result->elements, current_size * sizeof(int));
    if (temp) {
        result->elements = temp;
    }

    return result;
}

void print_tuple(const struct Tuple *tuple) {
    if (!tuple) return;
    printf("(");
    for (size_t i = 0; i < tuple->size; ++i) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

void free_tuple(struct Tuple *tuple) {
    if (tuple) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {4, 5, 6, 7, 8};

    struct Tuple tuple1;
    tuple1.elements = arr1;
    tuple1.size = sizeof(arr1) / sizeof(arr1[0]);

    struct Tuple tuple2;
    tuple2.elements = arr2;
    tuple2.size = sizeof(arr2) / sizeof(arr2[0]);

    struct Tuple *union_tuple = find_union(&tuple1, &tuple2);

    if (union_tuple) {
        print_tuple(union_tuple);
        free_tuple(union_tuple);
    } else {
        fprintf(stderr, "Failed to compute union.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}