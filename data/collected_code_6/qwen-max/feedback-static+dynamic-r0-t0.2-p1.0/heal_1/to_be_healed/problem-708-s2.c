#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(data);
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
    Node *head = NULL;
    Node *tail = NULL;
    /* Possible weaknesses found:
     * ASan: BUS
     */
    char *token = strtok((char *)str, delimiter);

    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        token = strtok(NULL, delimiter);
    }

    return head;
}

int main() {
    const char *input = "apple,banana,orange";
    const char *delimiter = ",";
    Node *list = string_to_list(input, delimiter);

    if (list == NULL) {
        printf("Failed to create list\n");
        return 1;
    }

    Node *current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    free_list(list);
    return 0;
}