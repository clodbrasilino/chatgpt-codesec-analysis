#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

static void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

static Node *create_node(const char *start, size_t len)
{
    if (len == SIZE_MAX || start == NULL) {
        return NULL;
    }

    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }

    if (len > 0) {
        memcpy(node->data, start, len);
    }
    node->data[len] = '\0';
    node->next = NULL;
    return node;
}

static size_t safe_strlen(const char *str, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Node *string_to_list(const char *str, const char *delim)
{
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    const char *start = str;
    const char *p = str;
    
    size_t delim_len = safe_strlen(delim, 4096);
    if (delim_len == 0 || delim_len >= 4096) {
        return NULL;
    }

    size_t remaining = safe_strlen(str, 1048576);
    if (remaining >= 1048576) {
        return NULL;
    }

    while (*p != '\0') {
        size_t check_len = safe_strlen(p, delim_len);
        if (check_len >= delim_len && memcmp(p, delim, delim_len) == 0) {
            size_t segment_len = (size_t)(p - start);
            Node *node = create_node(start, segment_len);
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

            p += delim_len;
            start = p;
        } else {
            p++;
        }
    }

    size_t final_len = (size_t)(p - start);
    Node *node = create_node(start, final_len);
    if (node == NULL) {
        free_list(head);
        return NULL;
    }

    if (head == NULL) {
        head = node;
    } else {
        tail->next = node;
    }

    return head;
}

int main(void)
{
    const char *input = "apple,banana,cherry,date";
    Node *list = string_to_list(input, ",");

    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    Node *current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }

    free_list(list);
    return EXIT_SUCCESS;
}