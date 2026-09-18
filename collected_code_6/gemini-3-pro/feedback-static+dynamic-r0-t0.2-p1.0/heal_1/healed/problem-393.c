#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    size_t length;
} List;

const List* find_max_length_list(const List* const* lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }

    const List* max_list = lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i] != NULL && (max_list == NULL || lists[i]->length > max_list->length)) {
            max_list = lists[i];
        }
    }

    return max_list;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list(void) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->length = 0;
    return new_list;
}

void append_node(List* list, int data) {
    if (list == NULL) {
        return;
    }
    Node* new_node = create_node(data);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
}

void free_list(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int main(void) {
    List* list1 = create_list();
    append_node(list1, 1);
    append_node(list1, 2);

    List* list2 = create_list();
    append_node(list2, 1);
    append_node(list2, 2);
    append_node(list2, 3);

    List* list3 = create_list();
    append_node(list3, 1);

    const List* const lists[] = {list1, list2, list3};
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);

    const List* max_list = find_max_length_list(lists, num_lists);

    if (max_list != NULL) {
        printf("Maximum length: %zu\n", max_list->length);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);

    return 0;
}