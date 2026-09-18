#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void free_list(Node* head);
Node* add_lists(const Node* list1, const Node* list2);
int append_node(Node** head, int data);
void print_list(const Node* head);

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

int append_node(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 1;
}

Node* add_lists(const Node* list1, const Node* list2) {
    Node* head = NULL;
    Node** tail = &head;

    while (list1 != NULL || list2 != NULL) {
        Node* new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        int sum = 0;
        if (list1 != NULL) {
            sum += list1->data;
            list1 = list1->next;
        }
        if (list2 != NULL) {
            sum += list2->data;
            list2 = list2->next;
        }

        new_node->data = sum;
        new_node->next = NULL;

        *tail = new_node;
        tail = &(new_node->next);
    }

    return head;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    if (!append_node(&list1, 1) || !append_node(&list1, 2) || !append_node(&list1, 3)) {
        free_list(list1);
        return EXIT_FAILURE;
    }

    if (!append_node(&list2, 4) || !append_node(&list2, 5)) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    result = add_lists(list1, list2);
    if (result == NULL) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    return EXIT_SUCCESS;
}