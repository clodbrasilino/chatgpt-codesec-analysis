#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

size_t count_lists(const List* head) {
    size_t count = 0;
    const List* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void free_nodes(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_lists(List* head) {
    while (head != NULL) {
        List* temp = head;
        head = head->next;
        free_nodes(temp->head);
        free(temp);
    }
}

int main(void) {
    List* head = NULL;
    List* current = NULL;
    int num_lists_to_create = 5;

    for (int i = 0; i < num_lists_to_create; i++) {
        List* new_list = (List*)malloc(sizeof(List));
        if (new_list == NULL) {
            free_lists(head);
            return EXIT_FAILURE;
        }
        new_list->head = NULL;
        new_list->next = NULL;

        if (head == NULL) {
            head = new_list;
            current = head;
        } else {
            current->next = new_list;
            current = current->next;
        }
    }

    size_t total_lists = count_lists(head);
    printf("%zu\n", total_lists);

    free_lists(head);

    return EXIT_SUCCESS;
}