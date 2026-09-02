#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void flatten_list(Node *head, int *output, int *index) {
    if (head == NULL) {
        return;
    }
    output[(*index)++] = head->value;
    flatten_list(head->next, output, index);
}

int main() {
    Node *head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);
    head->next->next->next = create_node(4);

    int *output = (int*)malloc(10 * sizeof(int));
    int index = 0;

    flatten_list(head, output, &index);

    for (int i = 0; i < index; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    free(output);

    return 0;
}