#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *new_node = malloc(sizeof *new_node);

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static Node *create_list(const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        Node *new_node = create_node(values[i]);

        if (new_node == NULL) {
            free_list(head);
            return NULL;
        }

        if (tail == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

static void print_list(const Node *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    putchar('\n');
}

static Node *interleave_lists(Node *list1, Node *list2)
{
    Node dummy;
    Node *tail = &dummy;

    dummy.data = 0;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        tail->next = list1;
        list1 = list1->next;
        tail = tail->next;

        tail->next = list2;
        list2 = list2->next;
        tail = tail->next;
    }

    tail->next = (list1 != NULL) ? list1 : list2;

    return dummy.next;
}

int main(void)
{
    const int values1[] = {1, 3, 5, 7, 9};
    const int values2[] = {2, 4, 6, 8, 10};
    const size_t count1 = sizeof values1 / sizeof values1[0];
    const size_t count2 = sizeof values2 / sizeof values2[0];
    Node *list1;
    Node *list2;
    Node *interleaved;

    list1 = create_list(values1, count1);
    if (list1 == NULL) {
        fprintf(stderr, "Error: failed to create the first list.\n");
        return EXIT_FAILURE;
    }

    list2 = create_list(values2, count2);
    if (list2 == NULL) {
        fprintf(stderr, "Error: failed to create the second list.\n");
        free_list(list1);
        return EXIT_FAILURE;
    }

    printf("List 1:      ");
    print_list(list1);
    printf("List 2:      ");
    print_list(list2);

    interleaved = interleave_lists(list1, list2);

    printf("Interleaved: ");
    print_list(interleaved);

    free_list(interleaved);

    return EXIT_SUCCESS;
}