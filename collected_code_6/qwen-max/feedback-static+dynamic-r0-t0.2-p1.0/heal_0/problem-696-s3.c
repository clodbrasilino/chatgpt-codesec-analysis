#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

List* create_list() {
    return (List*)malloc(sizeof(List));
}

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append_to_list(List *list, int value) {
    Node *new_node = create_node(value);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

List* zip_lists(List *list1, List *list2) {
    List *zipped_list = create_list();
    zipped_list->next = NULL;
    Node *current1 = list1->head;
    Node *current2 = list2->head;

    while (current1 != NULL || current2 != NULL) {
        if (current1 != NULL) {
            append_to_list(zipped_list, current1->value);
            current1 = current1->next;
        }
        if (current2 != NULL) {
            append_to_list(zipped_list, current2->value);
            current2 = current2->next;
        }
    }

    return zipped_list;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    List *list1 = create_list();
    List *list2 = create_list();

    append_to_list(list1, 1);
    append_to_list(list1, 3);
    append_to_list(list1, 5);

    append_to_list(list2, 2);
    append_to_list(list2, 4);
    append_to_list(list2, 6);

    List *zipped_list = zip_lists(list1, list2);
    print_list(zipped_list);

    return 0;
}