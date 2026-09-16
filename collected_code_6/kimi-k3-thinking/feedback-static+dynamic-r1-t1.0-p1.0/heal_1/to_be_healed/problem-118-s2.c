#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

static Node *create_node(char c)
{
    Node *node = malloc(sizeof *node);
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
        Node *next = head->next;
        free(head);
        head = next;
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

    if (str == NULL) {
        return NULL;
    }

    while (*str != '\0') {
        Node *node = create_node(*str);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
        str++;
    }

    return head;
}

void print_list(const Node *head)
{
    while (head != NULL) {
        if (putchar((unsigned char)head->data) == EOF) {
            return;
        }
        head = head->next;
    }
    putchar('\n');
}

int main(void)
{
    /* Possible weaknesses found:
     *  Assignment 'str="Hello, World!"', assigned value is "Hello, World!"
     */
    const char *str = "Hello, World!";
    Node *list = string_to_list(str);

    /* Possible weaknesses found:
     *  Condition 'str[0]!='\0'' is always true [knownConditionTrueFalse]
     *  Condition 'str[0]!='\0'' is always true
     */
    if (list == NULL && str[0] != '\0') {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    list = NULL;

    return EXIT_SUCCESS;
}