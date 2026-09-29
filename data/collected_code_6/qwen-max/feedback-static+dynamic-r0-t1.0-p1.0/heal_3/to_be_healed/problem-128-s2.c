#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(const char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->word = strdup(word);
    if (new_node->word == NULL) {
        free(new_node);
        return NULL;
    }
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
    if (dummy == NULL) return NULL;
    dummy->next = NULL;
    Node *tail = dummy;

    for (Node *current = head; current; current = current->next) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(current->word);
        if (len > (size_t)n) {
            tail->next = create_node(current->word);
            if (tail->next == NULL) {
                free(dummy);
                return NULL;
            }
            tail = tail->next;
        }
    }

    Node *result = dummy->next;
    free(dummy);
    return result;
}

int main() {
    Node *head = create_node("hello");
    if (head == NULL) return 1;
    head->next = create_node("world");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_node("abc");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next->next = create_node("programming");
    if (head->next->next->next == NULL) {
        free_list(head);
        return 1;
    }

    int n = 4;
    Node *long_words = filter_long_words(head, n);
    if (long_words == NULL) {
        free_list(head);
        return 1;
    }

    for (Node *current = long_words; current; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(long_words);
    free_list(head);

    return 0;
}