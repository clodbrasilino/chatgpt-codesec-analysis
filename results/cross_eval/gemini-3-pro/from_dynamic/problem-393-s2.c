#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct List {
    struct Node* head;
    size_t length;
};

struct List* find_max_length_list(struct List** lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    struct List* max_list = lists[0];
    size_t max_length = 0;

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL && lists[i]->length > max_length) {
            max_length = lists[i]->length;
            max_list = lists[i];
        }
    }

    return max_list;
}

void free_list(struct List* list) {
    if (list == NULL) return;
    
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->length = 0;
}

int main(void) {
    struct List list1 = {NULL, 3};
    struct List list2 = {NULL, 5};
    struct List list3 = {NULL, 2};

    struct List* lists[] = {&list1, &list2, &list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    struct List* max_list = find_max_length_list(lists, num_lists);

    if (max_list != NULL) {
        printf("Maximum length is: %zu\n", max_list->length);
    } else {
        printf("No valid lists provided.\n");
    }

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] != NULL) {
            free_list(lists[i]);
        }
    }

    return 0;
}