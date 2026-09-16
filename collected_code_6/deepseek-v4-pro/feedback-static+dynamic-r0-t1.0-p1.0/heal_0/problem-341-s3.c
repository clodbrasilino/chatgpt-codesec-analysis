#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Set;

typedef struct {
    int *tuple;
    int length;
} OrderedTuple;

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

OrderedTuple *convert_set_to_ordered_tuples(const Set *set, int tuple_size, int *num_tuples) {
    if (set == NULL || set->elements == NULL || set->size <= 0 || tuple_size <= 0 || num_tuples == NULL) {
        *num_tuples = 0;
        return NULL;
    }

    int *sorted_elements = (int *)malloc((size_t)set->size * sizeof(int));
    if (sorted_elements == NULL) {
        *num_tuples = 0;
        return NULL;
    }

    for (int i = 0; i < set->size; i++) {
        sorted_elements[i] = set->elements[i];
    }

    qsort(sorted_elements, (size_t)set->size, sizeof(int), compare_ints);

    int count = 0;
    for (int i = 0; i <= set->size - tuple_size; i += tuple_size) {
        count++;
    }
    int remaining = set->size % tuple_size;
    if (remaining > 0) {
        count++;
    }

    OrderedTuple *tuples = (OrderedTuple *)malloc((size_t)count * sizeof(OrderedTuple));
    if (tuples == NULL) {
        free(sorted_elements);
        *num_tuples = 0;
        return NULL;
    }

    int tuple_index = 0;
    for (int i = 0; i < set->size; i += tuple_size) {
        int current_length = tuple_size;
        if (i + tuple_size > set->size) {
            current_length = set->size - i;
        }

        int *tuple_data = (int *)malloc((size_t)current_length * sizeof(int));
        if (tuple_data == NULL) {
            for (int j = 0; j < tuple_index; j++) {
                free(tuples[j].tuple);
            }
            free(tuples);
            free(sorted_elements);
            *num_tuples = 0;
            return NULL;
        }

        for (int j = 0; j < current_length; j++) {
            tuple_data[j] = sorted_elements[i + j];
        }

        tuples[tuple_index].tuple = tuple_data;
        tuples[tuple_index].length = current_length;
        tuple_index++;
    }

    free(sorted_elements);
    *num_tuples = count;
    return tuples;
}

void free_ordered_tuples(OrderedTuple *tuples, int num_tuples) {
    if (tuples == NULL) {
        return;
    }

    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i].tuple);
    }
    free(tuples);
}

int main(void) {
    int elements[] = {5, 2, 9, 1, 7, 3, 8, 6, 4, 10};
    Set set;
    set.elements = elements;
    set.size = 10;

    int tuple_size = 3;
    int num_tuples = 0;

    OrderedTuple *tuples = convert_set_to_ordered_tuples(&set, tuple_size, &num_tuples);

    if (tuples == NULL) {
        printf("Error occurred during conversion.\n");
        return 1;
    }

    printf("Number of tuples: %d\n", num_tuples);
    for (int i = 0; i < num_tuples; i++) {
        printf("Tuple %d: (", i + 1);
        for (int j = 0; j < tuples[i].length; j++) {
            printf("%d", tuples[i].tuple[j]);
            if (j < tuples[i].length - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_ordered_tuples(tuples, num_tuples);
    return 0;
}