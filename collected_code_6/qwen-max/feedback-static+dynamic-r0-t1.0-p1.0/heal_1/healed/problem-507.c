#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(char *w) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = strdup(w);
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

Node* add_to_list(Node *head, char *word) {
    if (head == NULL) {
        return create_node(word);
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(word);
    return head;
}

Node* remove_words(Node *head, char *word_to_remove) {
    Node *dummy = create_node("");
    dummy->next = head;
    Node *prev = dummy;
    Node *current = head;

    while (current != NULL) {
        if (strcmp(current->word, word_to_remove) == 0) {
            prev->next = current->next;
            free(current->word);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
    Node *new_head = dummy->next;
    free(dummy->word);
    free(dummy);
    return new_head;
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%s\n", head->word);
        head = head->next;
    }
}

int main() {
    Node *words = NULL;
    words = add_to_list(words, "hello");
    words = add_to_list(words, "world");
    words = add_to_list(words, "hello");
    words = add_to_list(words, "again");

    printf("Original list:\n");
    print_list(words);

    words = remove_words(words, "hello");

    printf("List after removal:\n");
    print_list(words);

    free_list(words);
    return 0;
}