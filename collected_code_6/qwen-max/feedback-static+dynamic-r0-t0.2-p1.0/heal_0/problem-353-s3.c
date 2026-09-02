#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *down;
} List;

List* createNode(int value) {
    List *newNode = (List*)malloc(sizeof(List));
    newNode->head = (Node*)malloc(sizeof(Node));
    newNode->head->value = value;
    newNode->head->next = NULL;
    newNode->down = NULL;
    return newNode;
}

void append(List *list, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

List* addColumn(List *matrix, int colValue) {
    List *newCol = createNode(colValue);
    if (matrix == NULL) {
        return newCol;
    }

    List *current = matrix;
    while (current->down != NULL) {
        current = current->down;
    }
    current->down = newCol;
    return matrix;
}

List* removeColumn(List *matrix, int colIndex) {
    if (matrix == NULL || colIndex < 0) {
        return matrix;
    }

    List *prev = NULL;
    List *current = matrix;
    int index = 0;

    while (current != NULL && index < colIndex) {
        prev = current;
        current = current->down;
        index++;
    }

    if (current == NULL) {
        return matrix;
    }

    if (prev == NULL) {
        matrix = current->down;
    } else {
        prev->down = current->down;
    }

    Node *node = current->head;
    while (node != NULL) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
    free(current);

    return matrix;
}

void printMatrix(List *matrix) {
    List *current = matrix;
    while (current != NULL) {
        Node *node = current->head;
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("\n");
        current = current->down;
    }
}

int main() {
    List *matrix = NULL;

    matrix = addColumn(matrix, 1);
    append(matrix, 2);
    append(matrix, 3);

    matrix = addColumn(matrix, 4);
    append(matrix->down, 5);
    append(matrix->down, 6);

    matrix = addColumn(matrix, 7);
    append(matrix->down->down, 8);
    append(matrix->down->down, 9);

    printf("Original Matrix:\n");
    printMatrix(matrix);

    matrix = removeColumn(matrix, 1);

    printf("Matrix after removing column 1:\n");
    printMatrix(matrix);

    return 0;
}