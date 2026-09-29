#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
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

Node *string_to_list(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }

    char *str_copy = (char *)malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    strcpy(str_copy, str);

    Node *head = NULL;
    Node *tail = NULL;
    char *token = strtok(str_copy, delimiter);

    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free(str_copy);
            Node *current = head;
            while (current != NULL) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
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

    free(str_copy);
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    const char *delimiter = ",";

    Node *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}