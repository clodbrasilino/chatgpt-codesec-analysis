#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    int *elements;
    size_t size;
} List;

Tuple* add_list_to_tuples(Tuple *tuples, size_t num_tuples, const List *list) {
    if (tuples == NULL || list == NULL || list->elements == NULL) {
        return NULL;
    }

    Tuple *result_tuples = (Tuple *)malloc(num_tuples * sizeof(Tuple));
    if (result_tuples == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; i++) {
        size_t new_size = tuples[i].size + list->size;
        result_tuples[i].elements = (int *)malloc(new_size * sizeof(int));
        if (result_tuples[i].elements == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result_tuples[j].elements);
            }
            free(result_tuples);
            return NULL;
        }

        result_tuples[i].size = new_size;

        for (size_t j = 0; j < tuples[i].size; j++) {
            result_tuples[i].elements[j] = tuples[i].elements[j];
        }

        for (size_t j = 0; j < list->size; j++) {
            result_tuples[i].elements[tuples[i].size + j] = list->elements[j];
        }
    }

    return result_tuples;
}

void free_tuples(Tuple *tuples, size_t num_tuples) {
    if (tuples != NULL) {
        for (size_t i = 0; i < num_tuples; i++) {
            free(tuples[i].elements);
        }
        free(tuples);
    }
}

int main() {
    int tuple1_data[] = {1, 2};
    int tuple2_data[] = {3, 4, 5};
    Tuple tuples[2] = {
        {tuple1_data, 2},
        {tuple2_data, 3}
    };

    int list_data[] = {6, 7};
    List list = {list_data, 2};

    size_t num_tuples = 2;
    Tuple *new_tuples = add_list_to_tuples(tuples, num_tuples, &list);

    if (new_tuples != NULL) {
        for (size_t i = 0; i < num_tuples; i++) {
            printf("Tuple %zu: ", i);
            for (size_t j = 0; j < new_tuples[i].size; j++) {
                printf("%d ", new_tuples[i].elements[j]);
            }
            printf("\n");
        }
        free_tuples(new_tuples, num_tuples);
    } else {
        printf("Failed to add list to tuples.\n");
    }

    return 0;
}