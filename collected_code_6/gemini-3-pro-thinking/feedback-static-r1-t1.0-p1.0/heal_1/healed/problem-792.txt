#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

void free_nodes(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_lists(List* head) {
    List* current = head;
    while (current != NULL) {
        List* temp = current;
        current = current->next;
        free_nodes(temp->head);
        free(temp);
    }
}

size_t count_lists(const List* head) {
    if (!head) {
        return 0;
    }

    size_t count = 0;
    const List* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

List* create_list(void) {
    List* new_list = malloc(sizeof(List));
    if (!new_list) {
        return NULL;
    }
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

int main(void) {
    List* head_list = create_list();
    if (!head_list) {
        return EXIT_FAILURE;
    }

    head_list->next = create_list();
    if (!head_list->next) {
        free_lists(head_list);
        return EXIT_FAILURE;
    }

    head_list->next->next = create_list();
    if (!head_list->next->next) {
        free_lists(head_list);
        return EXIT_FAILURE;
    }

    size_t total_lists = count_lists(head_list);
    printf("%zu\n", total_lists);

    free_lists(head_list);

    return EXIT_SUCCESS;
}