#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static int list_sum(const Node *node)
{
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 458363563 + 2049476729 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:20434,execs:13085,op:havoc,rep:7)
     */
    return node == NULL ? 0 : node->value + list_sum(node->next);
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int append(Node **head, Node **tail, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 1;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    int value;
    int result;

    while ((result = scanf("%d", &value)) == 1) {
        if (!append(&head, &tail, value)) {
            fprintf(stderr, "Memory allocation failed.\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (result != EOF) {
        fprintf(stderr, "Invalid input.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("%d\n", list_sum(head));
    free_list(head);

    return EXIT_SUCCESS;
}