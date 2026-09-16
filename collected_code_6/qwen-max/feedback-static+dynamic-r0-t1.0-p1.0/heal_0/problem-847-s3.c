#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

List create_list(int value) {
    List list;
    list.head = (Node *)malloc(sizeof(Node));
    list.head->data = value;
    list.head->next = NULL;
    return list;
}

void copy_list(List *dest, const List *src) {
    if (!src->head) {
        dest->head = NULL;
        return;
    }

    Node *current_src = src->head;
    dest->head = (Node *)malloc(sizeof(Node));
    Node *current_dest = dest->head;
    current_dest->data = current_src->data;
    current_dest->next = NULL;

    while (current_src->next) {
        current_src = current_src->next;
        current_dest->next = (Node *)malloc(sizeof(Node));
        current_dest = current_dest->next;
        current_dest->data = current_src->data;
        current_dest->next = NULL;
    }
}

int main() {
    List original = create_list(42);
    List copy;
    copy_list(&copy, &original);

    // Print copied list
    for (Node *node = copy.head; node != NULL; node = node->next) {
        printf("%d\n", node->data);
    }

    // Free memory
    Node *current = copy.head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    current = original.head;
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}