#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node **current = &head;

    if (str == NULL) {
        return NULL;
    }

    for (const char *p = str; *p != '\0'; ++p) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        new_node->data = *p;
        new_node->next = NULL;
        *current = new_node;
        current = &new_node->next;
    }

    return head;
}

int main(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        Node *list = string_to_list(argv[i]);
        if (list == NULL) {
            fprintf(stderr, "Failed to convert string to list\n");
            return EXIT_FAILURE;
        }

        for (Node *n = list; n != NULL; n = n->next) {
            putchar(n->data);
        }
        putchar('\n');

        free_list(list);
    }

    return EXIT_SUCCESS;
}