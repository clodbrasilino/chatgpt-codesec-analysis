#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

Node *append_node(Node *head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return head;
    }
    if (head == NULL) {
        return new_node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

Node *remove_consecutive_duplicates(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    Node *current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *list = NULL;
    
    list = append_node(list, 1);
    list = append_node(list, 1);
    list = append_node(list, 2);
    list = append_node(list, 3);
    list = append_node(list, 3);
    list = append_node(list, 3);
    list = append_node(list, 4);
    list = append_node(list, 5);
    list = append_node(list, 5);

    print_list(list);

    list = remove_consecutive_duplicates(list);

    print_list(list);

    free_list(list);

    return 0;
}