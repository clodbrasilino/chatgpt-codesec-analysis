#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List* create_list(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->data = (int *)malloc(length * sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->length = length;
    return list;
}

void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

List* find_max_length_list(List *lists[], size_t count) {
    if (count == 0) {
        return NULL;
    }

    List *max_list = lists[0];
    for (size_t i = 1; i < count; ++i) {
        if (lists[i]->length > max_list->length) {
            max_list = lists[i];
        }
    }
    return max_list;
}

int main() {
    size_t lengths[] = {5, 10, 3, 8, 12};
    size_t count = sizeof(lengths) / sizeof(lengths[0]);
    List *lists[count];

    for (size_t i = 0; i < count; ++i) {
        lists[i] = create_list(lengths[i]);
        if (lists[i] == NULL) {
            for (size_t j = 0; j < i; ++j) {
                free_list(lists[j]);
            }
            return 1;
        }
    }

    List *max_list = find_max_length_list(lists, count);
    if (max_list != NULL) {
        printf("Max length: %zu\n", max_list->length);
    } else {
        printf("No list found.\n");
    }

    for (size_t i = 0; i < count; ++i) {
        free_list(lists[i]);
    }

    return 0;
}