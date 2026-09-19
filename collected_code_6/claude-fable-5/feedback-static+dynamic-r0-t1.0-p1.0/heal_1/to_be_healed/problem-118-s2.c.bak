#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node *create_node(char c)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = c;
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);

    for (i = 0; i < len; i++) {
        Node *node = create_node(str[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void print_list(const Node *head)
{
    const Node *current = head;
    while (current != NULL) {
        if (printf("%c -> ", current->data) < 0) {
            return;
        }
        current = current->next;
    }
    if (printf("NULL\n") < 0) {
        return;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     *  Assignment 'input="hello"', assigned value is "hello"
     */
    const char *input = "hello";
    Node *list;

    list = string_to_list(input);
    /* Possible weaknesses found:
     *  Condition 'input[0]!='\0'' is always true [knownConditionTrueFalse]
     *  Condition 'input[0]!='\0'' is always true
     */
    if (list == NULL && input[0] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}