#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {
        exit(EXIT_FAILURE);
    }
    n->data = data;
    n->next = NULL;
    return n;
}

void append_node(Node** head, int data) {
    Node* n = create_node(data);
    if (*head == NULL) {
        *head = n;
        return;
    }
    Node* cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = n;
}

void split_list(Node* source, int length, Node** front, Node** back) {
    if (front == NULL || back == NULL) {
        return;
    }
    if (source == NULL || length <= 0) {
        *front = NULL;
        *back = source;
        return;
    }

    Node* current = source;
    Node* prev = NULL;
    int count = 0;

    while (current != NULL && count < length) {
        prev = current;
        current = current->next;
        count++;
    }

    if (prev != NULL) {
        prev->next = NULL;
    }

    *front = source;
    *back = current;
}

void print_list(const Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node* head = NULL;
    Node* front = NULL;
    Node* back = NULL;

    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);

    split_list(head, 2, &front, &back);

    printf("Front: ");
    print_list(front);

    printf("Back: ");
    print_list(back);

    free_list(front);
    free_list(back);

    return 0;
}