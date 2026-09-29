#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(value);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char *str, const char *delimiter) {
    char *mutable_str = strdup(str);
    if (mutable_str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node **current = &head;
    char *token = strtok(mutable_str, delimiter);

    while (token != NULL) {
        *current = create_node(token);
        if (*current == NULL) {
            free_list(head);
            free(mutable_str);
            return NULL;
        }
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    free(mutable_str);
    return head;
}

int main() {
    const char *input = "python,programming";
    const char *delimiter = ",";
    Node *list = string_to_list(input, delimiter);

    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (Node *current = list; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(list);
    return 0;
}