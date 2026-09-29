#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
    struct List *next;
} List;

List* create_list(int *data, size_t size) {
    List *new_list = (List *)malloc(sizeof(List));
    new_list->data = (int *)malloc(size * sizeof(int));
    for (size_t i = 0; i < size; ++i) {
        new_list->data[i] = data[i];
    }
    new_list->size = size;
    new_list->next = NULL;
    return new_list;
}

void free_list(List *list) {
    while (list) {
        List *temp = list;
        free(list->data);
        list = list->next;
        free(temp);
    }
}

List* remove_empty_lists(List *head) {
    List *current = head;
    List *prev = NULL;

    while (current) {
        if (current->size == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            List *to_free = current;
            current = current->next;
            free(to_free->data);
            free(to_free);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

int main() {
    int data1[] = {1, 2, 3};
    int data2[] = {};
    int data3[] = {4, 5};

    List *head = create_list(data1, 3);
    head->next = create_list(data2, 0);
    head->next->next = create_list(data3, 2);

    head = remove_empty_lists(head);

    while (head) {
        for (size_t i = 0; i < head->size; ++i) {
            printf("%d ", head->data[i]);
        }
        printf("\n");
        head = head->next;
    }

    free_list(head);

    return 0;
}