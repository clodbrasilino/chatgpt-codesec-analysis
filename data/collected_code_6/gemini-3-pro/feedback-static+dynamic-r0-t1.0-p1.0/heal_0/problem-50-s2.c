#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append(List* list, int data) {
    if (!list) {
        return;
    }
    Node* new_node = create_node(data);
    if (!new_node) {
        return;
    }
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
    if (!list) {
        return;
    }
    Node* current = list->head;
    while (current) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
    list->head = NULL;
    list->length = 0;
}

List* find_min_length_list(List* lists, size_t num_lists) {
    if (!lists || num_lists == 0) {
        return NULL;
    }

    List* min_list = &lists[0];
    for (size_t i = 1; i < num_lists; ++i) {
        if (lists[i].length < min_list->length) {
            min_list = &lists[i];
        }
    }
    return min_list;
}

int main(void) {
    size_t num_lists = 3;
    List* lists = (List*)calloc(num_lists, sizeof(List));
    if (!lists) {
        return EXIT_FAILURE;
    }

    append(&lists[0], 1);
    append(&lists[0], 2);
    append(&lists[0], 3);

    append(&lists[1], 4);

    append(&lists[2], 5);
    append(&lists[2], 6);

    List* min_list = find_min_length_list(lists, num_lists);

    if (min_list) {
        printf("%zu\n", min_list->length);
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(&lists[i]);
    }
    free(lists);

    return EXIT_SUCCESS;
}