#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List* create_list(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->data = (int *)malloc(length * sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->length = length;
    for (size_t i = 0; i < length; ++i) {
        list->data[i] = i;
    }
    return list;
}

void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

List* find_min_length_lists(List **lists, size_t num_lists) {
    if (num_lists == 0) return NULL;
    size_t min_length = lists[0]->length;
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i]->length < min_length) {
            min_length = lists[i]->length;
        }
    }

    List *result = (List *)malloc(num_lists * sizeof(List *));
    if (result == NULL) return NULL;
    size_t count = 0;
    for (size_t i = 0; i < num_lists; ++i) {
        if (lists[i]->length == min_length) {
            result[count++] = lists[i];
        }
    }
    result[count] = NULL;
    return result;
}

int main() {
    List *list1 = create_list(5);
    List *list2 = create_list(3);
    List *list3 = create_list(3);
    List *list4 = create_list(7);

    List *lists[] = {list1, list2, list3, list4};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    List *min_lists = find_min_length_lists(lists, num_lists);

    for (size_t i = 0; min_lists[i] != NULL; ++i) {
        printf("List with minimum length: %zu\n", min_lists[i]->length);
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }
    free(min_lists);

    return 0;
}