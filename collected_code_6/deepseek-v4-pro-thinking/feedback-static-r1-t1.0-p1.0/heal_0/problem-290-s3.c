#include <stdio.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t length;
} List;

const List *find_list_of_lists_with_maximum_length(const List *lists, size_t count) {
    if (lists == NULL || count == 0) {
        return NULL;
    }

    const List *max_list = &lists[0];
    for (size_t i = 1; i < count; ++i) {
        if (lists[i].length > max_list->length) {
            max_list = &lists[i];
        }
    }

    return max_list;
}

int main(void) {
    int a[] = {1, 2};
    int b[] = {3, 4, 5, 6};
    int c[] = {7, 8, 9};

    List lists[] = {
        {a, sizeof(a) / sizeof(a[0])},
        {b, sizeof(b) / sizeof(b[0])},
        {c, sizeof(c) / sizeof(c[0])}
    };

    const List *max_list = find_list_of_lists_with_maximum_length(lists, sizeof(lists) / sizeof(lists[0]));

    if (max_list != NULL) {
        printf("Maximum length list has length %zu\n", max_list->length);
        printf("Elements:");
        for (size_t i = 0; i < max_list->length; ++i) {
            printf(" %d", max_list->data[i]);
        }
        printf("\n");
    }

    return 0;
}