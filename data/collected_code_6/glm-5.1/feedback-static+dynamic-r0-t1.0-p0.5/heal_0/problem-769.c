#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} List;

List list_create(size_t capacity) {
    List list;
    list.data = (int *)malloc(capacity * sizeof(int));
    list.size = 0;
    list.capacity = list.data != NULL ? capacity : 0;
    return list;
}

void list_append(List *list, int value) {
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        int *new_data = (int *)realloc(list->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = value;
}

void list_free(List *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

List list_difference(const List *list1, const List *list2) {
    List diff = list_create(list1->size > 0 ? list1->size : 1);
    if (diff.capacity == 0 && list1->size > 0) {
        return diff;
    }

    for (size_t i = 0; i < list1->size; i++) {
        int found = 0;
        for (size_t j = 0; j < list2->size; j++) {
            if (list1->data[i] == list2->data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            list_append(&diff, list1->data[i]);
        }
    }
    return diff;
}

int main(void) {
    List list1 = list_create(4);
    List list2 = list_create(4);

    list_append(&list1, 1);
    list_append(&list1, 2);
    list_append(&list1, 3);
    list_append(&list1, 4);

    list_append(&list2, 3);
    list_append(&list2, 4);
    list_append(&list2, 5);
    list_append(&list2, 6);

    List diff = list_difference(&list1, &list2);

    for (size_t i = 0; i < diff.size; i++) {
        printf("%d ", diff.data[i]);
    }
    printf("\n");

    list_free(&list1);
    list_free(&list2);
    list_free(&diff);

    return 0;
}