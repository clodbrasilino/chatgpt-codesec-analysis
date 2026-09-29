#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = strdup(str);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void insert_node(Node **head, const char *str) {
    Node *new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *head;
    *head = new_node;
}

void free_list(Node **head) {
    Node *current = *head;
    while (current != NULL) {
        Node *temp = current->next;
        free(current->data);
        free(current);
        current = temp;
    }
    *head = NULL;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node* string_to_list(const char *str, const char *delimiter) {
    char *mutable_str = strdup(str);
    if (mutable_str == NULL) {
        return NULL;
    }
    Node *head = NULL;
    char *token = strtok(mutable_str, delimiter);
    while (token != NULL) {
        insert_node(&head, token);
        token = strtok(NULL, delimiter);
    }
    free(mutable_str);
    return head;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main() {
    const char *input1 = "python,programming";
    const char *input2 = "write,a,program";
    const char *input3 = "lists,tuples,strings";
    const char *delimiter = ",";

    Node *head1 = string_to_list(input1, delimiter);
    print_list(head1);
    free_list(&head1);

    Node *head2 = string_to_list(input2, delimiter);
    print_list(head2);
    free_list(&head2);

    Node *head3 = string_to_list(input3, delimiter);
    print_list(head3);
    free_list(&head3);

    return 0;
}