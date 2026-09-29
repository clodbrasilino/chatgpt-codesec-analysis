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
    struct Node *node = create_node(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    struct Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

static size_t list_length(const struct Node *head)
{
    size_t count = 0U;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

static const struct Node *find_max_length_list(struct Node **lists, size_t num_lists, size_t *max_len)
{
    const struct Node *result = NULL;
    size_t best = 0U;

    if (lists == NULL || max_len == NULL) {
        return NULL;
    }

    for (size_t i = 0U; i < num_lists; i++) {
        size_t len = list_length(lists[i]);
        if (len > best) {
            best = len;
            result = lists[i];
        }
    }

    *max_len = best;
    return result;
}

static void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

static void print_list(const struct Node *head)
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
    int status = 0;

    for (int i = 1; i <= 3 && status == 0; i++) {
        status = append(&lists[0], i);
    }
    for (int i = 1; i <= 5 && status == 0; i++) {
        status = append(&lists[1], i * 10);
    }
    for (int i = 1; i <= 2 && status == 0; i++) {
        status = append(&lists[2], i * 100);
    }

    if (status != 0) {
        fprintf(stderr, "Memory allocation failed\n");
        for (size_t i = 0U; i < 3U; i++) {
            free_list(lists[i]);
        }
        return EXIT_FAILURE;
    }

    size_t max_len = 0U;
    const struct Node *longest = find_max_length_list(lists, 3U, &max_len);

    if (longest != NULL) {
        printf("Longest list has %zu elements: ", max_len);
        print_list(longest);
    } else {
        printf("All lists are empty\n");
    }

    for (size_t i = 0U; i < 3U; i++) {
        free_list(lists[i]);
    }

    return EXIT_SUCCESS;
}