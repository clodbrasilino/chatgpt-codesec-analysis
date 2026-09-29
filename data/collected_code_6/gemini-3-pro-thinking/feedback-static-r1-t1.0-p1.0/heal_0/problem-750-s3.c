#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} List;

bool list_init(List *list, size_t initial_capacity);
bool list_add_tuple(List *list, Tuple tuple);
void list_free(List *list);

bool list_init(List *list, size_t initial_capacity) {
    if (!list) {
        return false;
    }
    
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }
    
    list->data = malloc(initial_capacity * sizeof(Tuple));
    if (!list->data) {
        list->size = 0;
        list->capacity = 0;
        return false;
    }
    
    list->size = 0;
    list->capacity = initial_capacity;
    return true;
}

bool list_add_tuple(List *list, Tuple tuple) {
    if (!list || !list->data) {
        return false;
    }
    
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_data = realloc(list->data, new_capacity * sizeof(Tuple));
        if (!new_data) {
            return false;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    
    list->data[list->size] = tuple;
    list->size++;
    
    return true;
}

void list_free(List *list) {
    if (list) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int main(void) {
    List my_list;
    
    if (!list_init(&my_list, 2)) {
        return EXIT_FAILURE;
    }
    
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    
    if (!list_add_tuple(&my_list, t1) ||
        !list_add_tuple(&my_list, t2) ||
        !list_add_tuple(&my_list, t3)) {
        list_free(&my_list);
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < my_list.size; i++) {
        printf("(%d, %d)\n", my_list.data[i].first, my_list.data[i].second);
    }
    
    list_free(&my_list);
    return EXIT_SUCCESS;
}