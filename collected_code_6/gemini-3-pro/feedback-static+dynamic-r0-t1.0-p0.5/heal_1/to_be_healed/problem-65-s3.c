#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
int recursive_sum(const Node* head);
void free_list(Node* head);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int recursive_sum(const Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + recursive_sum(head->next);
}

void free_list(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* head = create_node(5);
    head->next = create_node(10);
    head->next->next = create_node(15);
    head->next->next->next = create_node(20);

    int sum = recursive_sum(head);
    printf("%d\n", sum);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}