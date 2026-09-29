#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *string_to_list(const char *str);
void print_list(const Node *head);
void free_list(Node *head);

int main(int argc, char *argv[])
{
    const char *input = (argc > 1) ? argv[1] : "Hello, World!";
    Node *list = string_to_list(input);

    if (list == NULL && input[0] != '\0') {
        fprintf(stderr, "Error: failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
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

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        while (*str != '\0' && isspace((unsigned char)*str)) {
            str++;
        }
        if (*str == '\0') {
            break;
        }

        const char *start = str;
        while (*str != '\0' && !isspace((unsigned char)*str)) {
            str++;
        }
        size_t len = (size_t)(str - start);

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        new_node->data = malloc(len + 1);
        if (new_node->data == NULL) {
            free(new_node);
            free_list(head);
            return NULL;
        }
        memcpy(new_node->data, start, len);
        new_node->data[len] = '\0';
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

void print_list(const Node *head)
{
    const Node *current = head;

    printf("[");
    while (current != NULL) {
        printf("'%s'", current->data);
        if (current->next != NULL) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}