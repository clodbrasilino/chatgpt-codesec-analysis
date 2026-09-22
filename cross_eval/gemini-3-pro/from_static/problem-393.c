#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct List {
    int* data;
    size_t length;
};

const struct List* find_max_length_list(const struct List* const* lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    const struct List* max_list = lists[0];
    
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i] != NULL) {
            if (max_list == NULL || lists[i]->length > max_list->length) {
                max_list = lists[i];
            }
        }
    }

    return max_list;
}

int main(void) {
    struct List list1;
    list1.data = NULL;
    list1.length = 5;

    struct List list2;
    list2.data = NULL;
    list2.length = 10;

    struct List list3;
    list3.data = NULL;
    list3.length = 3;

    const struct List* lists[] = {&list1, &list2, &list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    const struct List* max_list = find_max_length_list(lists, num_lists);

    if (max_list != NULL) {
        printf("Maximum length is: %zu\n", max_list->length);
    } else {
        printf("No valid lists provided.\n");
    }

    return 0;
}