#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
} List;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List* new_list = (List*)malloc(sizeof(List));
    if (!new_list) {
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->length = 0;
    return new_list;
}

void append(List* list, int data) {
    if (!list) return;
    
    Node* new_node = create_node(data);
    if (!list->head) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}

void free_list(List* list) {
    if (!list) return;
    
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List* find_min_length_list(List** lists, size_t num_lists) {
    if (!lists || num_lists == 0) {
        return NULL;
    }

    List* min_list = NULL;
    size_t min_length = SIZE_MAX;

    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i] && lists[i]->length < min_length) {
            min_length = lists[i]->length;
            min_list = lists[i];
        }
    }

    return min_list;
}

int main(void) {
    List* list1 = create_list();
    append(list1, 1);
    append(list1, 2);
    append(list1, 3);

    List* list2 = create_list();
    append(list2, 4);

    List* list3 = create_list();
    append(list3, 5);
    append(list3, 6);

    List* lists[] = {list1, list2, list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    List* min_list = find_min_length_list(lists, num_lists);

    if (min_list) {
        printf("%zu\n", min_list->length);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}