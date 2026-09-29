#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

static struct node *create_node(int value)
{
    struct node *n = malloc(sizeof(struct node));
    if (n == NULL) {
        return NULL;
    }
    n->value = value;
    n->next = NULL;
    return n;
}

static void free_list(struct node *head)
{
    while (head != NULL) {
        struct node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

static int append_node(struct node **head, int value)
{
    struct node *n = create_node(value);
    if (n == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = n;
        return 0;
    }
    struct node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = n;
    return 0;
}

static int insert_before_each(struct node **head, int value)
{
    if (head == NULL) {
        return -1;
    }
    struct node *cur = *head;
    struct node *prev = NULL;
    while (cur != NULL) {
        struct node *n = create_node(value);
        if (n == NULL) {
            return -1;
        }
        n->next = cur;
        if (prev == NULL) {
            *head = n;
        } else {
            prev->next = n;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

static void print_list(const struct node *head)
{
    const struct node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

int main(void)
{
    struct node *head = NULL;

    for (int i = 1; i <= 5; i++) {
        if (append_node(&head, i) != 0) {
            fprintf(stderr, "Allocation failure\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        fprintf(stderr, "Allocation failure\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("Modified list: ");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}