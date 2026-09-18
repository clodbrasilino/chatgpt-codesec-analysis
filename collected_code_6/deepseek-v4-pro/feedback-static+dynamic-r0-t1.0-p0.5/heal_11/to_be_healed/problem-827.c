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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 15, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  *  test case 2 failed: expected 9, got <no output>
  */

int sum_column(ListOfLists *list, int col) {
    if (list == NULL || col < 0) {
        return 0;
    }

    int sum = 0;
    Node *current = list->head;

    while (current != NULL) {
        if (current->data != NULL && col < current->size) {
            sum += current->data[col];
        }
        current = current->next;
    }

    return sum;
}

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(ListOfLists *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(list);
}

int main(void) {
    int *row1 = (int *)malloc(3 * sizeof(int));
    int *row2 = (int *)malloc(3 * sizeof(int));
    int *row3 = (int *)malloc(3 * sizeof(int));

    if (row1 == NULL || row2 == NULL || row3 == NULL) {
        free(row1);
        free(row2);
        free(row3);
        return 1;
    }

    row1[0] = 1; row1[1] = 2; row1[2] = 3;
    row2[0] = 4; row2[1] = 5; row2[2] = 6;
    row3[0] = 7; row3[1] = 8; row3[2] = 9;

    Node *node1 = create_node(row1, 3);
    if (node1 == NULL) {
        free(row1);
        free(row2);
        free(row3);
        return 1;
    }

    Node *node2 = create_node(row2, 3);
    if (node2 == NULL) {
        free(row1);
        free(row2);
        free(row3);
        free(node1);
        return 1;
    }

    Node *node3 = create_node(row3, 3);
    if (node3 == NULL) {
        free(row1);
        free(row2);
        free(row3);
        free(node1);
        free(node2);
        return 1;
    }

    node1->next = node2;
    node2->next = node3;

    ListOfLists list;
    list.head = node1;

    int result = sum_column(&list, 1);
    printf("%d\n", result);

    Node *current = list.head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}