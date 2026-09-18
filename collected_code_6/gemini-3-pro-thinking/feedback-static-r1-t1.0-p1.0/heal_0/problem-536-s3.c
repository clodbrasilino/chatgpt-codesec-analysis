#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
int append_node(Node** head, int data);
void free_list(Node* head);
int get_nth_item(const Node* head, size_t n, int* out_value);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int append_node(Node** head, int data) {
    Node* new_node = NULL;
    Node* current = NULL;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    
    return 0;
}

void free_list(Node* head) {
    Node* current = head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int get_nth_item(const Node* head, size_t n, int* out_value) {
    const Node* current = head;
    size_t count = 0;

    if (head == NULL || out_value == NULL) {
        return -1;
    }

    while (current != NULL) {
        if (count == n) {
            *out_value = current->data;
            return 0;
        }
        count++;
        current = current->next;
    }

    return -1;
}

int main(void) {
    Node* head = NULL;
    int value = 0;
    int status = 0;
    size_t i = 0;

    for (i = 0; i < 5; i++) {
        if (append_node(&head, (int)(i * 10)) != 0) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    status = get_nth_item(head, 2, &value);
    if (status == 0) {
        if (printf("%d\n", value) < 0) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    status = get_nth_item(head, 10, &value);
    if (status != 0) {
        if (printf("Item not found\n") < 0) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    free_list(head);
    return EXIT_SUCCESS;
}