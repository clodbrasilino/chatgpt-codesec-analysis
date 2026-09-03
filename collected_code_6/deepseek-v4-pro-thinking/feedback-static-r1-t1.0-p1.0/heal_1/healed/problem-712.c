#include <stdio.h>
#include <stdlib.h>

typedef struct InnerNode {
    int data;
    struct InnerNode *next;
} InnerNode;

typedef struct OuterNode {
    InnerNode *list;
    struct OuterNode *next;
} OuterNode;

InnerNode *inner_node_new(int data)
{
    InnerNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void inner_list_free(InnerNode *head)
{
    while (head != NULL) {
        InnerNode *next = head->next;
        free(head);
        head = next;
    }
}

InnerNode *inner_list_from_array(const int *values, int length)
{
    InnerNode *head = NULL;
    InnerNode **tail = &head;
    int i;

    for (i = 0; i < length; i++) {
        InnerNode *node = inner_node_new(values[i]);
        if (node == NULL) {
            inner_list_free(head);
            return NULL;
        }
        *tail = node;
        tail = &node->next;
    }

    return head;
}

int inner_list_equal(const InnerNode *a, const InnerNode *b)
{
    while (a != NULL && b != NULL) {
        if (a->data != b->data) {
            return 0;
        }
        a = a->next;
        b = b->next;
    }

    return a == NULL && b == NULL;
}

OuterNode *outer_node_new(InnerNode *list)
{
    OuterNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->list = list;
    node->next = NULL;
    return node;
}

int outer_list_append(OuterNode **head, InnerNode *list)
{
    OuterNode *node = outer_node_new(list);
    if (node == NULL) {
        return 0;
    }

    while (*head != NULL) {
        head = &(*head)->next;
    }

    *head = node;
    return 1;
}

void outer_list_free(OuterNode *head)
{
    while (head != NULL) {
        OuterNode *next = head->next;
        inner_list_free(head->list);
        free(head);
        head = next;
    }
}

OuterNode *remove_duplicates(OuterNode *head)
{
    OuterNode *current = head;

    while (current != NULL && current->next != NULL) {
        OuterNode *runner = current;

        while (runner->next != NULL) {
            if (inner_list_equal(current->list, runner->next->list)) {
                OuterNode *duplicate = runner->next;
                runner->next = duplicate->next;

                if (duplicate->list != current->list) {
                    inner_list_free(duplicate->list);
                }

                free(duplicate);
            } else {
                runner = runner->next;
            }
        }

        current = current->next;
    }

    return head;
}

void inner_list_print(const InnerNode *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
}

void outer_list_print(const OuterNode *head)
{
    printf("[");
    while (head != NULL) {
        printf("[");
        inner_list_print(head->list);
        printf("]");
        if (head->next != NULL) {
            printf(", ");
        }
        head = head->next;
    }
    printf("]\n");
}

static int append_values(OuterNode **head, const int *values, int length)
{
    InnerNode *list = inner_list_from_array(values, length);
    if (list == NULL) {
        return 0;
    }

    if (!outer_list_append(head, list)) {
        inner_list_free(list);
        return 0;
    }

    return 1;
}

int main(void)
{
    OuterNode *head = NULL;
    const int values1[] = {1, 2, 3};
    const int values2[] = {4, 5};
    const int values3[] = {1, 2, 3};
    const int values4[] = {6};
    const int values5[] = {4, 5};
    const int values6[] = {1, 2, 3};

    if (!append_values(&head, values1, 3) ||
        !append_values(&head, values2, 2) ||
        !append_values(&head, values3, 3) ||
        !append_values(&head, values4, 1) ||
        !append_values(&head, values5, 2) ||
        !append_values(&head, values6, 3)) {
        outer_list_free(head);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    outer_list_print(head);

    head = remove_duplicates(head);

    printf("After:  ");
    outer_list_print(head);

    outer_list_free(head);

    return EXIT_SUCCESS;
}