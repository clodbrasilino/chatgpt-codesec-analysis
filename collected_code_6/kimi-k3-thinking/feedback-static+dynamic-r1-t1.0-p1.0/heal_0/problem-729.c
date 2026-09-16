#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

struct Node *add_lists(const struct Node *list1, const struct Node *list2)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    while (list1 != NULL || list2 != NULL) {
        int sum = 0;
        struct Node *node;

        if (list1 != NULL) {
            sum += list1->data;
            list1 = list1->next;
        }
        if (list2 != NULL) {
            sum += list2->data;
            list2 = list2->next;
        }

        node = create_node(sum);
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
    }

    return head;
}

static int append_node(struct Node **head, int data)
{
    struct Node *node;
    struct Node *current;

    if (head == NULL) {
        return -1;
    }

    node = create_node(data);
    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

static void print_list(const struct Node *head)
{
    while (head != NULL) {
        printf("%d", head->data);
        if (head->next != NULL) {
            printf(" -> ");
        }
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *sum = NULL;
    int values1[] = {1, 2, 3, 4};
    int values2[] = {10, 20, 30, 40};
    size_t i;

    for (i = 0; i < sizeof(values1) / sizeof(values1[0]); i++) {
        if (append_node(&list1, values1[i]) != 0) {
            fprintf(stderr, "Error: failed to build list1\n");
            free_list(list1);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < sizeof(values2) / sizeof(values2[0]); i++) {
        if (append_node(&list2, values2[i]) != 0) {
            fprintf(stderr, "Error: failed to build list2\n");
            free_list(list1);
            free_list(list2);
            return EXIT_FAILURE;
        }
    }

    sum = add_lists(list1, list2);
    if (sum == NULL) {
        fprintf(stderr, "Error: failed to add lists\n");
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }

    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);
    printf("Sum:    ");
    print_list(sum);

    free_list(list1);
    free_list(list2);
    free_list(sum);

    return EXIT_SUCCESS;
}