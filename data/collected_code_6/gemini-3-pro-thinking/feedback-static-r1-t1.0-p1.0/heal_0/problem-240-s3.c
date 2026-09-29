#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

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
    if (head == NULL) {
        return -1;
    }

    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return 0;
}

void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(const Node* head) {
    const Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int replace_last_with_list(Node** head1, Node* head2) {
    if (head1 == NULL || *head1 == NULL) {
        return -1;
    }

    Node* prev = NULL;
    Node* curr = *head1;

    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }

    free(curr);

    if (prev == NULL) {
        *head1 = head2;
    } else {
        prev->next = head2;
    }

    return 0;
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    int status = 0;

    status |= append_node(&list1, 10);
    status |= append_node(&list1, 20);
    status |= append_node(&list1, 30);

    status |= append_node(&list2, 40);
    status |= append_node(&list2, 50);

    if (status != 0) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    print_list(list1);
    print_list(list2);

    if (replace_last_with_list(&list1, list2) != 0) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    print_list(list1);

    free_list(list1);

    return EXIT_SUCCESS;
}