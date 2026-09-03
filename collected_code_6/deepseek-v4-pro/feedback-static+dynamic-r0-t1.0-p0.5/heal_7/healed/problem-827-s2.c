#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} ListOfLists;

int sum_column(ListOfLists *list, int column) {
    if (list == NULL || list->head == NULL || column < 0) {
        return 0;
    }

    int sum = 0;
    Node *current = list->head;

    while (current != NULL) {
        if (current->data != NULL && column < current->size) {
            sum += current->data[column];
        }
        current = current->next;
    }

    return sum;
}

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        free(data);
        return NULL;
    }
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void append_node(ListOfLists *list, Node *node) {
    if (list == NULL || node == NULL) {
        return;
    }

    if (list->head == NULL) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

void free_list(ListOfLists *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
}

int main(void) {
    ListOfLists list = {0};

    int *row1 = (int *)malloc(3 * sizeof(int));
    if (row1 == NULL) {
        return 1;
    }
    row1[0] = 1;
    row1[1] = 2;
    row1[2] = 3;

    int *row2 = (int *)malloc(3 * sizeof(int));
    if (row2 == NULL) {
        free(row1);
        return 1;
    }
    row2[0] = 4;
    row2[1] = 5;
    row2[2] = 6;

    int *row3 = (int *)malloc(2 * sizeof(int));
    if (row3 == NULL) {
        free(row1);
        free(row2);
        return 1;
    }
    row3[0] = 7;
    row3[1] = 8;

    Node *node1 = create_node(row1, 3);
    if (node1 == NULL) {
        free(row2);
        free(row3);
        return 1;
    }

    Node *node2 = create_node(row2, 3);
    if (node2 == NULL) {
        free(row3);
        free(row1);
        free(node1);
        return 1;
    }

    Node *node3 = create_node(row3, 2);
    if (node3 == NULL) {
        free(row1);
        free(row2);
        free(node1);
        free(node2);
        return 1;
    }

    append_node(&list, node1);
    append_node(&list, node2);
    append_node(&list, node3);

    int result = sum_column(&list, 1);
    printf("%d\n", result);

    free_list(&list);

    return 0;
}