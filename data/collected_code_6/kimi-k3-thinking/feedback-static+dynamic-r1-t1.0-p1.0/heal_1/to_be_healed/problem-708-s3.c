#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

static Node *create_node(char data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *string_to_list(const char *str)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    for (i = 0; str[i] != '\0'; i++) {
        Node *node = create_node(str[i]);
        if (node == NULL) {
            /* Possible weaknesses found:
             *  previous implicit declaration is here
             *  call to undeclared function 'free_list'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'free_list' [-Wimplicit-function-declaration]
             */
            free_list(head);
            return NULL;
        }
        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    return head;
}

/* Possible weaknesses found:
 *  conflicting types for 'free_list'
 */
void free_list(Node *head)
{
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const Node *head)
{
    while (head != NULL) {
        putchar(head->data);
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
        fprintf(stderr, "Error: failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);
    list = NULL;

    return EXIT_SUCCESS;
}