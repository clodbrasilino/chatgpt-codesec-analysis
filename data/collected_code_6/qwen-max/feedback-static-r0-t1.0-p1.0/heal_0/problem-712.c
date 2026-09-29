#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List {
    int *data;
    size_t size;
} List;

int compare_lists(const void *a, const void *b) {
    List *list1 = (List *)a;
    List *list2 = (List *)b;
    if (list1->size != list2->size) return 1;
    for (size_t i = 0; i < list1->size; ++i) {
        if (list1->data[i] != list2->data[i]) return 1;
    }
    return 0;
}

void free_list(List *list) {
    free(list->data);
    free(list);
}

List* create_list(size_t size, int *data) {
    List *new_list = (List *)malloc(sizeof(List));
    if (!new_list) return NULL;
    new_list->size = size;
    new_list->data = (int *)malloc(size * sizeof(int));
    if (!new_list->data) {
        free(new_list);
        return NULL;
    }
    memcpy(new_list->data, data, size * sizeof(int));
    return new_list;
}

List** remove_duplicates(List **lists, size_t count, size_t *new_count) {
    qsort(lists, count, sizeof(List *), (int (*)(const void *, const void *))compare_lists);
    *new_count = 1;
    for (size_t i = 1; i < count; ++i) {
        if (compare_lists(lists[i - 1], lists[i])) {
            lists[(*new_count)++] = lists[i];
        } else {
            free_list(lists[i]);
        }
    }
    return lists;
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {1, 2, 3};
    int data4[] = {7, 8, 9};
    int data5[] = {4, 5, 6};

    List *list1 = create_list(3, data1);
    List *list2 = create_list(3, data2);
    List *list3 = create_list(3, data3);
    List *list4 = create_list(3, data4);
    List *list5 = create_list(3, data5);

    List *lists[] = {list1, list2, list3, list4, list5};
    size_t count = 5;
    size_t new_count;

    List **result = remove_duplicates(lists, count, &new_count);

    for (size_t i = 0; i < new_count; ++i) {
        for (size_t j = 0; j < result[i]->size; ++j) {
            printf("%d ", result[i]->data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < new_count; ++i) {
        free_list(result[i]);
    }

    return 0;
}