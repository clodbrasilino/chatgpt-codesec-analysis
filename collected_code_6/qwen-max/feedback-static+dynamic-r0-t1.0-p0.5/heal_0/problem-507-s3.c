#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(const char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->word = strdup(word);
    if (new_node->word == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, const char *word) {
    Node *new_node = create_node(word);
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

void remove_word(Node **head, const char *word) {
    Node *current = *head;
    Node *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current->word);
            free(current);
            current = previous ? previous->next : *head;
        } else {
            previous = current;
            current = current->next;
        }
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s -> ", current->word);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
}

int main() {
    Node *head = NULL;

    append_node(&head, "apple");
    append_node(&head, "banana");
    append_node(&head, "cherry");
    append_node(&head, "date");

    printf("Original list: ");
    print_list(head);

    remove_word(&head, "banana");
    remove_word(&head, "date");

    printf("List after removal: ");
    print_list(head);

    free_list(head);
    return 0;
}