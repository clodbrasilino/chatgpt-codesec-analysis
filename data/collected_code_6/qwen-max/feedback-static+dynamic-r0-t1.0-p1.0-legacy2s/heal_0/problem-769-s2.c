#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
} List;

List *create_list(size_t size) {
    List *list = (List *)malloc(sizeof(List));
    if (!list) return NULL;
    list->data = (int *)malloc(size * sizeof(int));
    if (!list->data) {
        free(list);
        return NULL;
    }
    list->size = size;
    return list;
}

void free_list(List *list) {
    if (list) {
        free(list->data);
        free(list);
    }
}

List *difference_lists(const List *list1, const List *list2) {
    size_t new_size = 0;
    for (size_t i = 0; i < list1->size; ++i) {
        int found = 0;
        for (size_t j = 0; j < list2->size; ++j) {
            if (list1->data[i] == list2->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) new_size++;
    }

    List *result = create_list(new_size);
    if (!result) return NULL;

    size_t index = 0;
    for (size_t i = 0; i < list1->size; ++i) {
        int found = 0;
        for (size_t j = 0; j < list2->size; ++j) {
            if (list1->data[i] == list2->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result->data[index++] = list1->data[i];
        }
    }
    return result;
}

int main() {
    List *list1 = create_list(5);
    List *list2 = create_list(3);

    if (!list1 || !list2) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    list1->data[0] = 1;
    list1->data[1] = 2;
    list1->data[2] = 3;
    list1->data[3] = 4;
    list1->data[4] = 5;

    list2->data[0] = 2;
    list2->data[1] = 4;
    list2->data[2] = 6;

    List *result = difference_lists(list1, list2);
    if (result) {
        for (size_t i = 0; i < result->size; ++i) {
            printf("%d ", result->data[i]);
        }
        printf("\n");
        free_list(result);
    }

    free_list(list1);
    free_list(list2);

    return 0;
}