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

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
}

int is_word_in_list(Node *head, const char *word) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node* remove_duplicates(const char *words[], int count) {
    Node *head = NULL;
    Node **tail = &head;

    for (int i = 0; i < count; ++i) {
        if (!is_word_in_list(head, words[i])) {
            *tail = create_node(words[i]);
            tail = &(*tail)->next;
        }
    }

    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s ", current->word);
        current = current->next;
    }
    printf("\n");
}

int main() {
    const char *words[] = {"apple", "banana", "apple", "orange", "banana", "grape"};
    int count = sizeof(words) / sizeof(words[0]);

    Node *unique_words = remove_duplicates(words, count);
    print_list(unique_words);

    free_list(unique_words);
    return 0;
}