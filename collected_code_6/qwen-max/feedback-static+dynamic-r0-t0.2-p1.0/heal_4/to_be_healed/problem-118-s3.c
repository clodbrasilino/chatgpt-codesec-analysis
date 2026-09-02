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
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char *str, const char *delimiter) {
    Node *head = NULL;
    Node **current = &head;
    char *str_copy = strdup(str);

    if (str_copy == NULL) {
        return NULL;
    }

    char *token = strtok(str_copy, delimiter);
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free_list(head);
            free(str_copy);
            return NULL;
        }
        *current = new_node;
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    free(str_copy);
    return head;
}

int main() {
    const char *input1 = "python,programming";
    const char *input2 = "lists,tuples,strings";
    const char *input3 = "write,a,program";
    const char *delimiter = ",";

    Node *list1 = string_to_list(input1, delimiter);
    for (Node *node = list1; node != NULL; node = node->next) {
        printf("%s\n", node->data);
    }
    free_list(list1);

    Node *list2 = string_to_list(input2, delimiter);
    for (Node *node = list2; node != NULL; node = node->next) {
        printf("%s\n", node->data);
    }
    free_list(list2);

    Node *list3 = string_to_list(input3, delimiter);
    for (Node *node = list3; node != NULL; node = node->next) {
        printf("%s\n", node->data);
    }
    free_list(list3);

    return 0;
}