#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = strdup(str);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char *str, const char *delimiter) {
    Node *head = NULL;
    Node **current = &head;
    char *copy = strdup(str);
    if (!copy) return NULL;
    char *token = strtok(copy, delimiter);

    while (token) {
        Node *new_node = create_node(token);
        if (!new_node) {
            free_list(head);
            free(copy);
            return NULL;
        }
        *current = new_node;
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    free(copy);
    return head;
}

int main() {
    const char *input = "python,programming";
    const char *delimiter = ",";
    Node *list = string_to_list(input, delimiter);

    if (!list) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (Node *node = list; node; node = node->next) {
        printf("%s\n", node->data);
    }

    free_list(list);
    return 0;
}