#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void append(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

Node* find_common_elements(Node* list1, Node* list2) {
    Node* common_list = NULL;
    Node* current1 = list1;
    while (current1 != NULL) {
        Node* current2 = list2;
        while (current2 != NULL) {
            if (current1->value == current2->value) {
                append(&common_list, current1->value);
                break;
            }
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return common_list;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    append(&list1, 1);
    append(&list1, 2);
    append(&list1, 3);
    append(&list1, 4);

    append(&list2, 2);
    append(&list2, 3);
    append(&list2, 5);

    Node* common_list = find_common_elements(list1, list2);

    print_list(common_list);

    free_list(list1);
    free_list(list2);
    free_list(common_list);

    return 0;
}