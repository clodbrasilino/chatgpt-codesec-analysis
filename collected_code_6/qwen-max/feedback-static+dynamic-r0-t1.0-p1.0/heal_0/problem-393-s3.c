#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List create_list(size_t len) {
    List list;
    list.data = (int *)malloc(len * sizeof(int));
    if (list.data != NULL) {
        list.length = len;
    } else {
        list.length = 0;
    }
    return list;
}

void free_list(List *list) {
    free(list->data);
    list->length = 0;
}

List find_max_length_list(List lists[], size_t num_lists) {
    if (num_lists == 0) {
        return (List){NULL, 0};
    }
    
    List max_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i].length > max_list.length) {
            max_list = lists[i];
        }
    }
    return max_list;
}

int main() {
    List lists[3];
    lists[0] = create_list(5);
    lists[1] = create_list(7);
    lists[2] = create_list(6);

    List max_list = find_max_length_list(lists, 3);

    printf("Max length: %zu\n", max_list.length);

    for (size_t i = 0; i < 3; ++i) {
        free_list(&lists[i]);
    }

    return 0;
}