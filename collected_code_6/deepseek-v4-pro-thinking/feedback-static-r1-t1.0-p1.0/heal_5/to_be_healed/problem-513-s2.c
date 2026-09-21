#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1048576

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head->data);
        free(head);
        head = next;
    }
}

static size_t safe_strlen(const char *s, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    if (len == max_len) {
        return (size_t)-1;
    }
    return len;
}

static Node *append_node_with_len(Node **head, Node **tail, const char *value, size_t len)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(node->data, value, len);
    node->data[len] = '\0';
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;

    return node;
}

Node *convert_tuple_to_list(const char **tuple, int length, const char *separator)
{
    if (tuple == NULL || length <= 0 || separator == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    size_t sep_len = safe_strlen(separator, MAX_STRING_LENGTH);
    if (sep_len == (size_t)-1) {
        return NULL;
    }

    for (int i = 0; i < length; ++i) {
        const char *element = (tuple[i] != NULL) ? tuple[i] : "";
        size_t elem_len = safe_strlen(element, MAX_STRING_LENGTH);
        if (elem_len == (size_t)-1) {
            free_list(head);
            return NULL;
        }

        if (append_node_with_len(&head, &tail, element, elem_len) == NULL) {
            free_list(head);
            return NULL;
        }

        if (append_node_with_len(&head, &tail, separator, sep_len) == NULL) {
            free_list(head);
            return NULL;
        }
    }

    return head;
}

static void print_list(const Node *head)
{
    for (const Node *current = head; current != NULL; current = current->next) {
        printf("%s ", current->data);
    }
    printf("\n");
}

int main(void)
{
    const char *tuple[] = { "apple", "banana", "cherry" };
    const char *separator = "-";

    Node *list = convert_tuple_to_list(tuple, 3, separator);
    if (list == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}