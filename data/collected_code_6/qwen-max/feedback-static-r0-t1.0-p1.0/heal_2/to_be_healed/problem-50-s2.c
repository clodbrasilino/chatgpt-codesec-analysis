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
        list->data[i] = i;
    }
    return list;
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

/* Possible weaknesses found:
 *  expected 'const List **' but argument is of type 'List * const*'
 */
List* find_min_length_list(const List **lists, size_t count) {
    if (count == 0) {
        return NULL;
    }
    const List *min_list = lists[0];
    for (size_t i = 1; i < count; ++i) {
        if (lists[i]->length < min_list->length) {
            min_list = lists[i];
        }
    }
    return (List *)min_list;
}

int main() {
    size_t num_lists = 4;
    List *lists[num_lists];

    lists[0] = create_list(5);
    lists[1] = create_list(3);
    lists[2] = create_list(7);
    lists[3] = create_list(2);

    List *const *const_lists = (List *const *)lists;
    /* Possible weaknesses found:
     *  passing argument 1 of 'find_min_length_list' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    const List *min_list = find_min_length_list(const_lists, num_lists);

    if (min_list != NULL) {
        printf("Min length: %zu\n", min_list->length);
    } else {
        printf("No list found.\n");
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }

    return 0;
}