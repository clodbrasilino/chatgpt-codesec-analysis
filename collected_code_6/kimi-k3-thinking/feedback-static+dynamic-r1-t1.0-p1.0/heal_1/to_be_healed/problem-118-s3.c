#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  */

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        Node *new_node = (Node *)malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }
        new_node->data = str[i];
        new_node->next = NULL;

        if (tail == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

int print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (putchar((unsigned char)current->data) == EOF) {
            return -1;
        }
        current = current->next;
    }

    if (putchar('\n') == EOF) {
        return -1;
    }

    return 0;
}

int main(void)
{
    const char *str = "Hello, World!";
    Node *list = string_to_list(str);

    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    if (print_list(list) != 0) {
        fprintf(stderr, "Failed to print list\n");
        free_list(list);
        return EXIT_FAILURE;
    }

    free_list(list);
    list = NULL;

    return EXIT_SUCCESS;
}