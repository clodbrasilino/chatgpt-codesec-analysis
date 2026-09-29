#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
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

Node* string_to_list(const char *str) {
    Node *head = NULL;
    const char *delim = " ";
    char *token = strtok((char *)str, delim);
    while (token != NULL) {
        append_to_list(&head, token);
        token = strtok(NULL, delim);
    }
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    const char *input = "This is a test string";
    /* Possible weaknesses found:
     * ASan: BUS
     */
    Node *list = string_to_list(input);
    print_list(list);
    free_list(list);
    return 0;
}