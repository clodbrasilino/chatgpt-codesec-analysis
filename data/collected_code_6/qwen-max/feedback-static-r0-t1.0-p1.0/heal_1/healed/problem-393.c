#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List* create_list(size_t length) {
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->data = malloc(length * sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->length = length;
    for (size_t i = 0; i < length; ++i) {
        list->data[i] = 0;
    }
    return list;
}

void free_list(List *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

const List* find_max_length_list(const List *lists[], size_t num_lists) {
    if (num_lists == 0) return NULL;
    const List *max_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i]->length > max_list->length) {
            max_list = lists[i];
        }
    }
    return max_list;
}

int main() {
    size_t num_lists = 3;
    List *lists[3] = {create_list(5), create_list(7), create_list(3)};
    const List *max_list = find_max_length_list((const List *const*)lists, num_lists);

    if (max_list) {
        printf("Max length: %zu\n", max_list->length);
    } else {
        printf("No list found.\n");
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }

    return 0;
}