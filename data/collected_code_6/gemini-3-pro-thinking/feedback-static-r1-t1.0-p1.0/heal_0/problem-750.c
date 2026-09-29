#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *elements;
    size_t count;
    size_t capacity;
} List;

int init_list(List *list, size_t initial_capacity);
int add_tuple(List *list, Tuple tuple);
void free_list(List *list);

int init_list(List *list, size_t initial_capacity) {
    if (list == NULL) {
        return -1;
    }

    if (initial_capacity == 0) {
        initial_capacity = 1;
    }

    list->elements = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->elements == NULL) {
        list->count = 0;
        list->capacity = 0;
        return -1;
    }

    list->count = 0;
    list->capacity = initial_capacity;

    return 0;
}

int add_tuple(List *list, Tuple tuple) {
    if (list == NULL) {
        return -1;
    }

    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        if (new_capacity == 0) {
            new_capacity = 2;
        }

        Tuple *new_elements = (Tuple *)realloc(list->elements, new_capacity * sizeof(Tuple));
        if (new_elements == NULL) {
            return -1;
        }

        list->elements = new_elements;
        list->capacity = new_capacity;
    }

    list->elements[list->count] = tuple;
    list->count++;

    return 0;
}

void free_list(List *list) {
    if (list != NULL) {
        free(list->elements);
        list->elements = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int main(void) {
    List my_list;
    
    if (init_list(&my_list, 2) != 0) {
        fprintf(stderr, "Failed to initialize list.\n");
        return EXIT_FAILURE;
    }

    Tuple t1 = {10, 20};
    if (add_tuple(&my_list, t1) != 0) {
        fprintf(stderr, "Failed to add tuple.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    Tuple t2 = {30, 40};
    if (add_tuple(&my_list, t2) != 0) {
        fprintf(stderr, "Failed to add tuple.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    Tuple t3 = {50, 60};
    if (add_tuple(&my_list, t3) != 0) {
        fprintf(stderr, "Failed to add tuple.\n");
        free_list(&my_list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < my_list.count; i++) {
        printf("Tuple %zu: (%d, %d)\n", i, my_list.elements[i].first, my_list.elements[i].second);
    }

    free_list(&my_list);

    return EXIT_SUCCESS;
}