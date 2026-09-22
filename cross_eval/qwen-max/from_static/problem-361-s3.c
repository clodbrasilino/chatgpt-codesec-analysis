#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
} List;

List* create_list(size_t size) {
    List *new_list = (List*) malloc(sizeof(List));
    new_list->size = size;
    new_list->data = (int*) malloc(size * sizeof(int));
    return new_list;
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

List** remove_empty_lists(List **lists, size_t *count) {
    size_t i, j;
    for (i = 0, j = 0; i < *count; ++i) {
        if (lists[i]->size > 0) {
            lists[j++] = lists[i];
        } else {
            free_list(lists[i]);
        }
    }
    *count = j;
    return lists;
}

int main() {
    size_t count = 3;
    List **lists = (List**) malloc(count * sizeof(List*));

    lists[0] = create_list(0);
    lists[1] = create_list(2);
    lists[1]->data[0] = 1;
    lists[1]->data[1] = 2;
    lists[2] = create_list(0);

    lists = remove_empty_lists(lists, &count);

    for (size_t i = 0; i < count; ++i) {
        for (size_t k = 0; k < lists[i]->size; ++k) {
            printf("%d ", lists[i]->data[k]);
        }
        printf("\n");
        free_list(lists[i]);
    }
    free(lists);

    return 0;
}