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

    for (size_t i = 0; i < num_tuples; ++i) {
        size_t new_size = tuples[i].size + list->size;
        int *new_elements = realloc(tuples[i].elements, new_size * sizeof(int));
        
        if (new_elements == NULL) {
            return NULL; 
        }

        for (size_t j = 0; j < list->size; ++j) {
            new_elements[tuples[i].size + j] = list->elements[j];
        }

        tuples[i].elements = new_elements;
        tuples[i].size = new_size;
    }

    return tuples;
}

void free_tuples(Tuple *tuples, size_t num_tuples) {
    if (tuples != NULL) {
        for (size_t i = 0; i < num_tuples; ++i) {
            free(tuples[i].elements);
        }
        free(tuples);
    }
}

int main() {
    size_t num_tuples = 2;
    Tuple *tuples = malloc(num_tuples * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].size = 2;
    tuples[0].elements = malloc(tuples[0].size * sizeof(int));
    if (tuples[0].elements == NULL) {
        free(tuples);
        return EXIT_FAILURE;
    }
    tuples[0].elements[0] = 1;
    tuples[0].elements[1] = 2;

    tuples[1].size = 3;
    tuples[1].elements = malloc(tuples[1].size * sizeof(int));
    if (tuples[1].elements == NULL) {
        free(tuples[0].elements);
        free(tuples);
        return EXIT_FAILURE;
    }
    tuples[1].elements[0] = 3;
    tuples[1].elements[1] = 4;
    tuples[1].elements[2] = 5;

    int list_data[] = {6, 7};
    List list;
    list.elements = list_data;
    list.size = 2;

    if (add_list_to_tuples(tuples, num_tuples, &list) == NULL) {
        free_tuples(tuples, num_tuples);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < tuples[i].size; ++j) {
            printf("%d ", tuples[i].elements[j]);
        }
        printf("\n");
    }

    free_tuples(tuples, num_tuples);

    return EXIT_SUCCESS;
}