#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *items;
    size_t size;
} List;

List* create_list(size_t size, int initial) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) return NULL;
    list->items = (int*)calloc(size, sizeof(int));
    if (!list->items) {
        free(list);
        return NULL;
    }
    list->size = size;
    for (size_t i = 0; i < size; ++i) {
        list->items[i] = initial;
    }
    return list;
}

void free_list(List* list) {
    if (list) {
        free(list->items);
        free(list);
    }
}

void swap_first_and_last(List* list) {
    if (list && list->size > 1) {
        int temp = list->items[0];
        list->items[0] = list->items[list->size - 1];
        list->items[list->size - 1] = temp;
    }
}

void print_list(const List* list) {
    if (list) {
        for (size_t i = 0; i < list->size; ++i) {
            printf("%d ", list->items[i]);
        }
        printf("\n");
    }
}

int main() {
    List* list = create_list(5, 0);
    if (list) {
        list->items[0] = 1;
        list->items[1] = 2;
        list->items[2] = 3;
        list->items[3] = 4;
        list->items[4] = 5;
        
        printf("Original List: ");
        print_list(list);

        swap_first_and_last(list);

        printf("Modified List: ");
        print_list(list);

        free_list(list);
    }

    return 0;
}