#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

int init_tuple_list(TupleList *list, size_t capacity) {
    if (list == NULL || capacity == 0) {
        return 0;
    }
    list->tuples = malloc(capacity * sizeof(Tuple));
    if (list->tuples == NULL) {
        return 0;
    }
    list->count = 0;
    list->capacity = capacity;
    return 1;
}

int add_tuple(TupleList *list, const int *elements, size_t size) {
    if (list == NULL || elements == NULL || size == 0) {
        return 0;
    }
    if (list->count >= list->capacity) {
        return 0;
    }
    list->tuples[list->count].elements = malloc(size * sizeof(int));
    if (list->tuples[list->count].elements == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i++) {
        list->tuples[list->count].elements[i] = elements[i];
    }
    list->tuples[list->count].size = size;
    list->count++;
    return 1;
}

int all_elements_divisible(const Tuple *tuple, int k) {
    if (tuple == NULL || tuple->elements == NULL || k == 0) {
        return 0;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] % k != 0) {
            return 0;
        }
    }
    return 1;
}

int find_tuples_divisible_by_k(const TupleList *list, int k, TupleList *result) {
    if (list == NULL || result == NULL || k == 0) {
        return 0;
    }
    for (size_t i = 0; i < list->count; i++) {
        if (all_elements_divisible(&list->tuples[i], k)) {
            if (!add_tuple(result, list->tuples[i].elements, list->tuples[i].size)) {
                return 0;
            }
        }
    }
    return 1;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
        list->tuples[i].elements = NULL;
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
    list->capacity = 0;
}

void print_tuple_list(const TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }
}

int main(void) {
    TupleList input;
    TupleList result;
    int k = 2;

    if (!init_tuple_list(&input, 10)) {
        fprintf(stderr, "Failed to initialize input list\n");
        return EXIT_FAILURE;
    }

    if (!init_tuple_list(&result, 10)) {
        fprintf(stderr, "Failed to initialize result list\n");
        free_tuple_list(&input);
        return EXIT_FAILURE;
    }

    int t1[] = {2, 4, 6};
    int t2[] = {3, 6, 9};
    int t3[] = {4, 8, 12};
    int t4[] = {5, 10, 15};
    int t5[] = {6, 12, 18};

    if (!add_tuple(&input, t1, 3) ||
        !add_tuple(&input, t2, 3) ||
        !add_tuple(&input, t3, 3) ||
        !add_tuple(&input, t4, 3) ||
        !add_tuple(&input, t5, 3)) {
        fprintf(stderr, "Failed to add tuples\n");
        free_tuple_list(&input);
        free_tuple_list(&result);
        return EXIT_FAILURE;
    }

    printf("Input tuples:\n");
    print_tuple_list(&input);

    if (!find_tuples_divisible_by_k(&input, k, &result)) {
        fprintf(stderr, "Failed to find tuples\n");
        free_tuple_list(&input);
        free_tuple_list(&result);
        return EXIT_FAILURE;
    }

    printf("\nTuples with all elements divisible by %d:\n", k);
    print_tuple_list(&result);

    free_tuple_list(&input);
    free_tuple_list(&result);

    return EXIT_SUCCESS;
}