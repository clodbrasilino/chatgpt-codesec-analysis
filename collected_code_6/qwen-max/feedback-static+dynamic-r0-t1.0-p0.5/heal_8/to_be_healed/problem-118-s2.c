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
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
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
    char *mutable_str = strdup(str);
    if (mutable_str == NULL) return NULL;
    char *token = strtok(mutable_str, " ");
    while (token != NULL) {
        append_to_list(&head, token);
        token = strtok(NULL, " ");
    }
    free(mutable_str);
    return head;
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

int main() {
    const char *input1 = "lists tuples strings";
    const char *input2 = "python programming";
    const char *input3 = "write a program";
    const char *input4 = "This is a test string";

    for (int i = 0; i < 4; i++) {
        const char *input = (i == 0) ? input1 : (i == 1) ? input2 : (i == 2) ? input3 : input4;
        Node *list = string_to_list(input);
        if (list == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }

        for (Node *current = list; current != NULL; current = current->next) {
            printf("%s\n", current->data);
        }

        free_list(list);
        printf("\n");
    }

    return 0;
}