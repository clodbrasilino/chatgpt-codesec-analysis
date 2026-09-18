#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(const char *word) {
    if (!word) return NULL;
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    new_node->word = strdup(word);
    if (!new_node->word) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}

Node* remove_words(Node *head, const char **words_to_remove, int num_words_to_remove) {
    if (!head || !words_to_remove || num_words_to_remove <= 0) return head;

    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *current = head;

    while (current) {
        int should_remove = 0;
        for (int i = 0; i < num_words_to_remove; ++i) {
            if (words_to_remove[i] && strcmp(current->word, words_to_remove[i]) == 0) {
                should_remove = 1;
                break;
            }
        }

        if (should_remove) {
            prev->next = current->next;
            free(current->word);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return dummy.next;
}

void print_list(Node *head) {
    Node *current = head;
    while (current) {
        printf("%s\n", current->word);
        current = current->next;
    }
}

int main(void) {
    Node *head = create_node("apple");
    if (!head) return 1;
    
    head->next = create_node("banana");
    if (!head->next) { free_list(head); return 1; }
    
    head->next->next = create_node("cherry");
    if (!head->next->next) { free_list(head); return 1; }
    
    head->next->next->next = create_node("date");
    if (!head->next->next->next) { free_list(head); return 1; }

    const char *words_to_remove[] = {"banana", "date"};
    int num_words_to_remove = 2;

    head = remove_words(head, words_to_remove, num_words_to_remove);

    print_list(head);

    free_list(head);

    return 0;
}