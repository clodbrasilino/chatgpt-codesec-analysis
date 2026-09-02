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
    return list;
}

void free_list(List *list) {
    if (list != NULL) {
        if (list->data != NULL) {
            free(list->data);
        }
        free(list);
    }
}

List* find_min_length_list(List **lists, size_t num_lists) {
    if (num_lists == 0) return NULL;
    
    List *min_length_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i]->length < min_length_list->length) {
            min_length_list = lists[i];
        }
    }
    return min_length_list;
}

int main() {
    List *list1 = create_list(5);
    List *list2 = create_list(3);
    List *list3 = create_list(7);

    List *lists[] = {list1, list2, list3};
    size_t num_lists = 3;

    /* Possible weaknesses found:
     *  Variable 'min_list' can be declared as pointer to const [constVariablePointer]
     */
    List *min_list = find_min_length_list(lists, num_lists);
    if (min_list != NULL) {
        printf("Minimum length list has %zu elements\n", min_list->length);
    } else {
        printf("No list is found.\n");
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}