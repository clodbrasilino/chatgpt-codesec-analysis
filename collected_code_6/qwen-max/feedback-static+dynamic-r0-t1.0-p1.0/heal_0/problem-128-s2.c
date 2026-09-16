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
    while (current) {
        Node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
}

Node* filter_long_words(Node *head, int n) {
    Node *dummy = (Node *)malloc(sizeof(Node));
    dummy->next = NULL;
    Node *tail = dummy;

    for (Node *current = head; current; current = current->next) {
        if (strlen(current->word) > n) {
            tail->next = create_node(current->word);
            tail = tail->next;
        }
    }

    Node *result = dummy->next;
    free(dummy);
    return result;
}

int main() {
    Node *head = create_node("hello");
    head->next = create_node("world");
    head->next->next = create_node("abc");
    head->next->next->next = create_node("programming");

    int n = 4;
    Node *long_words = filter_long_words(head, n);

    for (Node *current = long_words; current; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(long_words);
    free_list(head);

    return 0;
}