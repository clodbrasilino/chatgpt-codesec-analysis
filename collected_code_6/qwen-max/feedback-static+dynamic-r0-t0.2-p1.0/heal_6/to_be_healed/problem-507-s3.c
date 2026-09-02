#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(char *word) {
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
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  */

Node* remove_words(Node *head, const char *word_to_remove) {
    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *current = head;

    while (current != NULL) {
        Node *next_node = current->next;
        if (strcmp(current->word, word_to_remove) == 0) {
            prev->next = next_node;
            free(current->word);
            free(current);
        } else {
            prev = current;
        }
        current = next_node;
    }

    return dummy.next;
}

int main() {
    Node *head = create_node("red");
    head->next = create_node("green");
    head->next->next = create_node("blue");
    head->next->next->next = create_node("white");

    const char *word_to_remove = "blue";
    head = remove_words(head, word_to_remove);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(head);

    head = create_node("red");
    head->next = create_node("green");
    head->next->next = create_node("blue");
    head->next->next->next = create_node("black");

    word_to_remove = "black";
    head = remove_words(head, word_to_remove);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(head);

    head = create_node("red");
    head->next = create_node("green");
    head->next->next = create_node("black");
    head->next->next->next = create_node("orange");

    word_to_remove = "black";
    head = remove_words(head, word_to_remove);

    for (Node *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->word);
    }

    free_list(head);
    return 0;
}