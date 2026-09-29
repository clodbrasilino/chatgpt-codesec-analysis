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
    size_t count = 0U;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

static void free_list(struct Node *head)
{
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

/* Possible weaknesses found:
 *  Parameter 'lists' can be declared as const array [constParameter]
 */
static int find_min_length_list(struct Node *const lists[], size_t num_lists, size_t *min_index)
{
    size_t i;
    size_t min_len;

    if (lists == NULL || min_index == NULL || num_lists == 0U) {
        return -1;
    }
    *min_index = 0U;
    min_len = list_length(lists[0]);
    for (i = 1U; i < num_lists; i++) {
        size_t len = list_length(lists[i]);
        if (len < min_len) {
            min_len = len;
            *min_index = i;
        }
    }
    return 0;
}

int main(void)
{
    struct Node *lists[3] = { NULL, NULL, NULL };
    size_t min_index = 0U;
    int status = EXIT_SUCCESS;
    size_t i;

    if (append(&lists[0], 1) != 0 ||
        append(&lists[0], 2) != 0 ||
        append(&lists[0], 3) != 0) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS) {
        if (append(&lists[1], 10) != 0 ||
            append(&lists[1], 20) != 0) {
            status = EXIT_FAILURE;
        }
    }

    if (status == EXIT_SUCCESS) {
        if (append(&lists[2], 100) != 0 ||
            append(&lists[2], 200) != 0 ||
            append(&lists[2], 300) != 0 ||
            append(&lists[2], 400) != 0) {
            status = EXIT_FAILURE;
        }
    }

    if (status == EXIT_SUCCESS) {
        if (find_min_length_list(lists, 3U, &min_index) != 0) {
            status = EXIT_FAILURE;
        } else {
            if (printf("List with minimum length is at index %zu with length %zu\n",
                       min_index, list_length(lists[min_index])) < 0) {
                status = EXIT_FAILURE;
            }
        }
    }

    for (i = 0U; i < 3U; i++) {
        free_list(lists[i]);
        lists[i] = NULL;
    }

    return status;
}