#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

Node* create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) exit(EXIT_FAILURE);
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

List* create_list() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) exit(EXIT_FAILURE);
    list->head = NULL;
    return list;
}

void free_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List* pack_duplicates(List *input_list) {
    List *result = create_list();
    if (input_list->head == NULL) {
        return result;
    }

    Node *current = input_list->head;
    Node *start_of_dup = current;

    while (current != NULL && current->next != NULL) {
        if (current->value == current->next->value) {
            current = current->next;
        } else {
            List *sublist = create_list();
            Node *node = start_of_dup;
            do {
                append_to_list(sublist, node->value);
                node = node->next;
            } while (node != current->next);

            append_to_list(result, (int)(uintptr_t)sublist);
            start_of_dup = current->next;
            current = current->next;
        }
    }

    if (start_of_dup != NULL) {
        List *sublist = create_list();
        Node *node = start_of_dup;
        while (node != NULL) {
            append_to_list(sublist, node->value);
            node = node->next;
        }
        append_to_list(result, (int)(uintptr_t)sublist);
    }

    return result;
}

void print_list(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        if ((uintptr_t)current->value > 0x10000) {
            List *sublist = (List *)((uintptr_t)current->value);
            printf("[ ");
            Node *subnode = sublist->head;
            while (subnode != NULL) {
                printf("%d ", subnode->value);
                subnode = subnode->next;
            }
            printf("] ");
        } else {
            printf("%d ", current->value);
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    List *list = create_list();
    append_to_list(list, 1);
    append_to_list(list, 1);
    append_to_list(list, 2);
    append_to_list(list, 3);
    append_to_list(list, 3);
    append_to_list(list, 3);
    append_to_list(list, 4);

    printf("Original list: ");
    print_list(list);

    List *packed = pack_duplicates(list);

    printf("Packed list: ");
    print_list(packed);

    free_list(list);
    Node *current = packed->head;
    while (current != NULL) {
        if ((uintptr_t)current->value > 0x10000) {
            free_list((List *)((uintptr_t)current->value));
        }
        current = current->next;
    }
    free_list(packed);

    return 0;
}