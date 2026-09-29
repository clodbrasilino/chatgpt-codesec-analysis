#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
void push_back(Node** head, int data);
bool contains(const Node* list, int target_val);
Node* remove_elements(Node* target, const Node* reference);
void free_list(Node* head);
void print_list(const Node* head);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push_back(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

bool contains(const Node* list, int target_val) {
    const Node* current = list;
    while (current) {
        if (current->data == target_val) {
            return true;
        }
        current = current->next;
    }
    return false;
}

Node* remove_elements(Node* target, const Node* reference) {
    if (!target || !reference) {
        return target;
    }

    Node* current = target;
    Node* prev = NULL;

    while (current) {
        if (contains(reference, current->data)) {
            Node* temp = current;
            if (!prev) {
                target = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return target;
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list_a = NULL;
    Node* list_b = NULL;

    push_back(&list_a, 1);
    push_back(&list_a, 2);
    push_back(&list_a, 3);
    push_back(&list_a, 4);
    push_back(&list_a, 5);

    push_back(&list_b, 2);
    push_back(&list_b, 4);
    push_back(&list_b, 6);

    list_a = remove_elements(list_a, list_b);

    print_list(list_a);

    free_list(list_a);
    free_list(list_b);

    return EXIT_SUCCESS;
}