#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct SubList {
    int value;
    int count;
    struct SubList *next;
} SubList;

SubList *pack_duplicates(Node *list) {
    if (list == NULL) {
        return NULL;
    }

    SubList *head = NULL;
    SubList *tail = NULL;
    Node *current = list;

    while (current != NULL) {
        int current_value = current->data;
        int count = 0;

        while (current != NULL && current->data == current_value) {
            count++;
            current = current->next;
        }

        SubList *new_sublist = (SubList *)malloc(sizeof(SubList));
        if (new_sublist == NULL) {
            SubList *temp = head;
            while (temp != NULL) {
                SubList *next = temp->next;
                free(temp);
                temp = next;
            }
            return NULL;
        }

        new_sublist->value = current_value;
        new_sublist->count = count;
        new_sublist->next = NULL;

        if (head == NULL) {
            head = new_sublist;
            tail = new_sublist;
        } else {
            tail->next = new_sublist;
            tail = new_sublist;
        }
    }

    return head;
}

void free_sublists(SubList *list) {
    while (list != NULL) {
        SubList *temp = list;
        list = list->next;
        free(temp);
    }
}

void free_nodes(Node *list) {
    while (list != NULL) {
        Node *temp = list;
        list = list->next;
        free(temp);
    }
}

Node *create_node(int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void print_sublists(SubList *list) {
    while (list != NULL) {
        printf("[%d, %d] ", list->value, list->count);
        list = list->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;

    int values[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 5, 5, 1, 1};
    int size = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < size; i++) {
        Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            free_nodes(head);
            return 1;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    SubList *packed = pack_duplicates(head);

    if (packed != NULL) {
        print_sublists(packed);
        free_sublists(packed);
    }

    free_nodes(head);

    return 0;
}