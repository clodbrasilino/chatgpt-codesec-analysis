#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

static int append(struct Node **head, int value)
{
    struct Node *node;
    struct Node *cur;

    if (head == NULL) {
        return -1;
    }

    node = create_node(value);
    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

static size_t list_length(const struct Node *head)
{
    size_t count = 0;
    const struct Node *cur = head;

    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

static const struct Node *find_max_length_list(const struct Node *const *lists,
                                               size_t num_lists,
                                               size_t *max_len)
{
    const struct Node *max_list = NULL;
    size_t best = 0;
    size_t i;

    if (lists == NULL || max_len == NULL) {
        return NULL;
    }

    for (i = 0; i < num_lists; i++) {
        size_t len = list_length(lists[i]);
        if (max_list == NULL || len > best) {
            best = len;
            max_list = lists[i];
        }
    }

    *max_len = best;
    return max_list;
}

static void free_list(struct Node *head)
{
    struct Node *cur = head;

    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
}

static void print_list(const struct Node *head)
{
    const struct Node *cur = head;

    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main(void)
{
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *list3 = NULL;
    const struct Node *lists[3];
    const struct Node *max_list;
    size_t max_len = 0;
    int status = EXIT_SUCCESS;
    int i;

    for (i = 1; i <= 3; i++) {
        if (append(&list1, i) != 0) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    for (i = 1; i <= 5; i++) {
        if (append(&list2, i * 10) != 0) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    for (i = 1; i <= 2; i++) {
        if (append(&list3, i * 100) != 0) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;

    max_list = find_max_length_list(lists, 3, &max_len);
    if (max_list == NULL) {
        fprintf(stderr, "No list found\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("Maximum length: %zu\n", max_len);
    printf("List contents: ");
    print_list(max_list);

cleanup:
    free_list(list1);
    free_list(list2);
    free_list(list3);
    return status;
}