#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(const char *word) {
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
    Node dummy = {NULL, head};
    Node *prev = &dummy;
    Node *current = head;

    while (current) {
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

    return dummy.next;
}

int main() {
    Node *head = create_node("red");
    if (!head) return -1;
    head->next = create_node("green");
    if (!head->next) return -1;
    head->next->next = create_node("blue");
    if (!head->next->next) return -1;
    head->next->next->next = create_node("black");
    if (!head->next->next->next) return -1;

    const char *word_to_remove = "blue";
    head = remove_words(head, word_to_remove);

    for (Node *current = head; current; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(head);
    return 0;
}