#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char *str, const char *delimiter) {
    Node *head = NULL;
    Node **current = &head;
    char *token = strtok((char *)str, delimiter);

    while (token != NULL) {
        *current = create_node(token);
        if (*current == NULL) {
            return NULL;
        }
        current = &(*current)->next;
        token = strtok(NULL, delimiter);
    }

    return head;
}

void free_list(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main() {
    const char *input = "apple,banana,orange,grape";
    const char *delimiter = ",";
    Node *list = string_to_list(input, delimiter);

    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }

    for (Node *node = list; node != NULL; node = node->next) {
        printf("%s\n", node->data);
    }

    free_list(list);
    return 0;
}