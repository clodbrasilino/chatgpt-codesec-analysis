#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    int size;
    int capacity;
} TupleList;

void init_list(TupleList *list) {
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int append_tuple(TupleList *list, int first, int second) {
    if (list->size >= list->capacity) {
        int new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size].first = first;
    list->data[list->size].second = second;
    list->size++;
    return 1;
}

void free_list(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int max_similar_indices(const TupleList *list1, const TupleList *list2) {
    int min_size = (list1->size < list2->size) ? list1->size : list2->size;
    int max_val = 0;
    int found = 0;

    for (int i = 0; i < min_size; i++) {
        if (list1->data[i].first == list2->data[i].first &&
            list1->data[i].second == list2->data[i].second) {
            if (!found || i > max_val) {
                max_val = i;
                found = 1;
            }
        }
    }

    return found ? max_val : -1;
}

int main(void) {
    TupleList list1;
    TupleList list2;
    int result;

    init_list(&list1);
    init_list(&list2);

    if (!append_tuple(&list1, 1, 2) ||
        !append_tuple(&list1, 3, 4) ||
        !append_tuple(&list1, 5, 6) ||
        !append_tuple(&list1, 7, 8)) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(&list1);
        free_list(&list2);
        return EXIT_FAILURE;
    }

    if (!append_tuple(&list2, 1, 2) ||
        !append_tuple(&list2, 9, 10) ||
        !append_tuple(&list2, 5, 6) ||
        !append_tuple(&list2, 11, 12)) {
        fprintf(stderr, "Memory allocation failed\n");
        free_list(&list1);
        free_list(&list2);
        return EXIT_FAILURE;
    }

    result = max_similar_indices(&list1, &list2);
    if (result != -1) {
        printf("Maximum similar index: %d\n", result);
        printf("Tuple at that index: (%d, %d)\n", 
               list1.data[result].first, list1.data[result].second);
    } else {
        printf("No similar tuples found\n");
    }

    free_list(&list1);
    free_list(&list2);

    return EXIT_SUCCESS;
}