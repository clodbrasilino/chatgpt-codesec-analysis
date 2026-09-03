#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void append_to_list(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) return;
    if (*head == NULL) *head = new_node;
    else {
        Node *current = *head;
        while (current->next != NULL) current = current->next;
        current->next = new_node;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["python",""
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* string_to_list(const char *str) {
    Node *head = NULL;
    const char *delim = " ";
    char *str_copy = strdup(str);
    if (str_copy == NULL) return NULL;
    char *token = strtok(str_copy, delim);
    while (token != NULL) {
        append_to_list(&head, token);
        token = strtok(NULL, delim);
    }
    free(str_copy);
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main() {
    const char *input = "This is a test string";
    Node *list = string_to_list(input);

    for (Node *current = list; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(list);
    return 0;
}