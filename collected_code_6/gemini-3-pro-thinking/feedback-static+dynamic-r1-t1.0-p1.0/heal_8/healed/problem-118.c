#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str);
void free_list(Node *head);
Node* string_to_list(const char *str);

Node* create_node(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    strcpy(new_node->data, str);
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

Node* string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    char *copy = (char *)malloc(strlen(str) + 1);
    if (copy == NULL) {
        return NULL;
    }
    strcpy(copy, str);

    Node *head = NULL;
    Node *tail = NULL;

    char *token = strtok(copy, " \t\n\r");
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free_list(head);
            free(copy);
            return NULL;
        }

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        token = strtok(NULL, " \t\n\r");
    }

    free(copy);
    return head;
}

int main(void) {
    char buffer[4096];
    
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        Node *list_head = string_to_list(buffer);

        printf("[");
        Node *current = list_head;
        while (current != NULL) {
            printf("'%s'", current->data);
            if (current->next != NULL) {
                printf(", ");
            }
            current = current->next;
        }
        printf("]\n");

        free_list(list_head);
    }

    return EXIT_SUCCESS;
}