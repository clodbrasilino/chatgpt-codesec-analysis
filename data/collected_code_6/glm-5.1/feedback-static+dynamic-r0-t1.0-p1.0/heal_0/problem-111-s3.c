#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} InnerList;

typedef struct {
    InnerList *lists;
    size_t count;
} NestedList;

InnerList create_inner_list(size_t capacity) {
    InnerList list;
    list.data = (int *)malloc(capacity * sizeof(int));
    list.size = 0;
    list.capacity = capacity;
    return list;
}

void add_to_inner_list(InnerList *list, int value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size++] = value;
}

void free_inner_list(InnerList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

NestedList create_nested_list(size_t count) {
    NestedList nl;
    nl.count = count;
    nl.lists = (InnerList *)malloc(count * sizeof(InnerList));
    return nl;
}

void free_nested_list(NestedList *nl) {
    for (size_t i = 0; i < nl->count; i++) {
        free_inner_list(&nl->lists[i]);
    }
    free(nl->lists);
    nl->lists = NULL;
    nl->count = 0;
}

InnerList find_common_elements(NestedList nl) {
    InnerList result = create_inner_list(10);
    if (nl.count == 0) return result;

    for (size_t i = 0; i < nl.lists[0].size; i++) {
        int candidate = nl.lists[0].data[i];
        int is_duplicate = 0;
        for (size_t j = 0; j < result.size; j++) {
            if (result.data[j] == candidate) {
                is_duplicate = 1;
                break;
            }
        }
        if (is_duplicate) continue;

        int found_in_all = 1;
        for (size_t j = 1; j < nl.count; j++) {
            int found_in_current = 0;
            for (size_t k = 0; k < nl.lists[j].size; k++) {
                if (nl.lists[j].data[k] == candidate) {
                    found_in_current = 1;
                    break;
                }
            }
            if (!found_in_current) {
                found_in_all = 0;
                break;
            }
        }
        if (found_in_all) {
            add_to_inner_list(&result, candidate);
        }
    }
    return result;
}

int main(void) {
    NestedList nl = create_nested_list(3);

    nl.lists[0] = create_inner_list(5);
    add_to_inner_list(&nl.lists[0], 1);
    add_to_inner_list(&nl.lists[0], 2);
    add_to_inner_list(&nl.lists[0], 3);
    add_to_inner_list(&nl.lists[0], 4);

    nl.lists[1] = create_inner_list(5);
    add_to_inner_list(&nl.lists[1], 2);
    add_to_inner_list(&nl.lists[1], 3);
    add_to_inner_list(&nl.lists[1], 5);

    nl.lists[2] = create_inner_list(5);
    add_to_inner_list(&nl.lists[2], 3);
    add_to_inner_list(&nl.lists[2], 2);
    add_to_inner_list(&nl.lists[2], 6);

    InnerList common = find_common_elements(nl);

    for (size_t i = 0; i < common.size; i++) {
        printf("%d ", common.data[i]);
    }
    printf("\n");

    free_inner_list(&common);
    free_nested_list(&nl);

    return 0;
}