#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->value = strdup(str);
    if (new_node->value == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

Node* append_to_list(Node *head, const char *str) {
    if (head == NULL) return create_node(str);
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(str);
    return head;
}

Node* tuple_to_list(Node *tuple, const char *str) {
    if (tuple == NULL) return NULL;
    Node *list = create_node(tuple->value);
    if (list == NULL) return NULL;
    tuple = tuple->next;
    while (tuple != NULL) {
        list = append_to_list(list, str);
        if (tuple->value == NULL) break;
        list = append_to_list(list, tuple->value);
        tuple = tuple->next;
    }
    return list;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%s -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *tuple = create_node("1");
    tuple = append_to_list(tuple, "2");
    tuple = append_to_list(tuple, "3");

    const char *separator = "X";
    Node *list = tuple_to_list(tuple, separator);

    print_list(list);

    free_list(tuple);
    free_list(list);

    return 0;
}