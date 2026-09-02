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
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  */

Node* remove_words(Node *head, const char *word_to_remove) {
    Node *dummy = (Node *)malloc(sizeof(Node));
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
    free(dummy);
    return new_head;
}

int main() {
    Node *head = create_node("apple");
    head->next = create_node("banana");
    head->next->next = create_node("apple");
    head->next->next->next = create_node("cherry");

    head = remove_words(head, "apple");

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(head);
    return 0;
}