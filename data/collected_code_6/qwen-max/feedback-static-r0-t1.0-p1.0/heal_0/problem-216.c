#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

void init_list(List *list) {
    list->head = NULL;
    list->tail = NULL;
}

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(List *list, int value) {
    Node *new_node = create_node(value);
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

bool is_subset(const List *smaller, const List *larger) {
    for (const Node *node = smaller->head; node != NULL; node = node->next) {
        bool found = false;
        for (const Node *compare = larger->head; compare != NULL; compare = compare->next) {
            if (compare->value == node->value) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main() {
    List list1, list2;
    init_list(&list1);
    init_list(&list2);

    add_to_list(&list1, 1);
    add_to_list(&list1, 2);
    add_to_list(&list1, 3);

    add_to_list(&list2, 1);
    add_to_list(&list2, 2);
    add_to_list(&list2, 3);
    add_to_list(&list2, 4);
    add_to_list(&list2, 5);

    if (is_subset(&list1, &list2)) {
        printf("list1 is a subset of list2\n");
    } else {
        printf("list1 is not a subset of list2\n");
    }

    return 0;
}