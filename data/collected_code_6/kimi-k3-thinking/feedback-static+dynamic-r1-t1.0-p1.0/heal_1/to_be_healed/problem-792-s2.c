#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

/* Possible weaknesses found:
 *  Parameter 'heads' can be declared as const array [constParameter]
 */
static size_t count_lists(Node *const heads[], size_t num_lists)
{
    size_t count = 0;
    size_t i;

    if (heads == NULL) {
        return 0;
    }

    for (i = 0; i < num_lists; i++) {
        if (heads[i] != NULL) {
            count++;
        }
    }

    return count;
}

static size_t count_nodes(const Node *head)
{
    size_t count = 0;

    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    enum { NUM_LISTS = 4 };
    Node *lists[NUM_LISTS] = {NULL, NULL, NULL, NULL};
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0; i < (size_t)(NUM_LISTS - 1); i++) {
        size_t j;

        for (j = 0; j <= i; j++) {
            Node *node = create_node((int)(i * 10 + j));

            if (node == NULL) {
                fprintf(stderr, "Error: memory allocation failed\n");
                status = EXIT_FAILURE;
                break;
            }

            node->next = lists[i];
            lists[i] = node;
        }

        if (status == EXIT_FAILURE) {
            break;
        }
    }

    if (status == EXIT_SUCCESS) {
        printf("Number of non-empty lists: %zu\n",
               count_lists(lists, (size_t)NUM_LISTS));

        for (i = 0; i < (size_t)NUM_LISTS; i++) {
            printf("List %zu contains %zu node(s)\n", i, count_nodes(lists[i]));
        }
    }

    for (i = 0; i < (size_t)NUM_LISTS; i++) {
        free_list(lists[i]);
        lists[i] = NULL;
    }

    return status;
}