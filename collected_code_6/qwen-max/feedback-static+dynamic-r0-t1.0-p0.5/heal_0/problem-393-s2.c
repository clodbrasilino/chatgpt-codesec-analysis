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
    for (size_t i = 0; i < length; ++i) {
        list->data[i] = 0;
    }
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
    List *list1 = create_list(5);
    List *list2 = create_list(10);
    List *list3 = create_list(3);

    List *lists[] = {list1, list2, list3};
    size_t count = 3;

    List *max_list = find_max_length_list(lists, count);
    if (max_list != NULL) {
        printf("Max length: %zu\n", max_list->length);
    } else {
        printf("No list found.\n");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}