#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(value);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

Node* string_to_list(const char *str, const char *delimiter) {
    char *mutable_str = strdup(str);
    if (mutable_str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node **current = &head;
    char *token = strtok(mutable_str, delimiter);

    while (token != NULL) {
        *current = create_node(token);
        if (*current == NULL) {
            free_list(head);
            free(mutable_str);
            return NULL;
        }
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    free(mutable_str);
    return head;
}

int main() {
    const char *input1 = "lists,tuples,strings";
    const char *input2 = "write a program";
    const char *input3 = "python,programming";
    const char *delim1 = ",";
    const char *delim2 = " ";
    const char *delim3 = ",";

    Node *list1 = string_to_list(input1, delim1);
    Node *list2 = string_to_list(input2, delim2);
    Node *list3 = string_to_list(input3, delim3);

    if (list1 == NULL || list2 == NULL || list3 == NULL) {
        fprintf(stderr, "Failed to create list\n");
        free_list(list1);
        free_list(list2);
        free_list(list3);
        return 1;
    }

    for (Node *current = list1; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    for (Node *current = list2; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    for (Node *current = list3; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(list1);
    free_list(list2);
    free_list(list3);
    return 0;
}