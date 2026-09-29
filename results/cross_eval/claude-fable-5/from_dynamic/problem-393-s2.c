#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append(struct Node **head, int data)
{
    struct Node *node;
    struct Node *cur;

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

    cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

size_t list_length(const struct Node *head)
{
    size_t count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

struct Node *find_max_length_list(struct Node **lists, size_t num_lists, size_t *max_len)
{
    struct Node *max_list = NULL;
    size_t best = 0;
    size_t i;

    if (lists == NULL || max_len == NULL) {
        return NULL;
    }

    for (i = 0; i < num_lists; i++) {
        size_t len = list_length(lists[i]);
        if (len > best) {
            best = len;
            max_list = lists[i];
        }
    }

    *max_len = best;
    return max_list;
}

void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

void print_list(const struct Node *head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
    struct Node *lists[3] = { NULL, NULL, NULL };
    size_t max_len = 0;
    struct Node *max_list;
    size_t i;
    int status = EXIT_SUCCESS;

    if (append(&lists[0], 1) != 0 ||
        append(&lists[0], 2) != 0 ||
        append(&lists[0], 3) != 0) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (append(&lists[1], 10) != 0 ||
        append(&lists[1], 20) != 0 ||
        append(&lists[1], 30) != 0 ||
        append(&lists[1], 40) != 0 ||
        append(&lists[1], 50) != 0) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (append(&lists[2], 100) != 0 ||
        append(&lists[2], 200) != 0) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    max_list = find_max_length_list(lists, 3, &max_len);
    if (max_list == NULL) {
        fprintf(stderr, "No non-empty list found\n");
        status = EXIT_FAILURE;
        goto cleanup;
    }

    printf("Maximum length: %zu\n", max_len);
    printf("List contents: ");
    print_list(max_list);

cleanup:
    for (i = 0; i < 3; i++) {
        free_list(lists[i]);
        lists[i] = NULL;
    }

    return status;
}