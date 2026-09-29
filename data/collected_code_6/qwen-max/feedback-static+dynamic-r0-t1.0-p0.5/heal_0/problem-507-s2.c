#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, char *word) {
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

int remove_word_from_list(Node **head, const char *word) {
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
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
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
        Node *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

int main() {
    Node *head = NULL;

    append_to_list(&head, "apple");
    append_to_list(&head, "banana");
    append_to_list(&head, "cherry");
    append_to_list(&head, "date");

    print_list(head);

    remove_word_from_list(&head, "banana");
    remove_word_from_list(&head, "date");

    print_list(head);

    free_list(head);
    return 0;
}