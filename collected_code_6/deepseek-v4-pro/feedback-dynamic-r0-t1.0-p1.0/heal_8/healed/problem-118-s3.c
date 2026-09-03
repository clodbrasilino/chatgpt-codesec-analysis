#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *str;
    struct ListNode *next;
} ListNode;

ListNode *create_node(const char *str) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }
    node->str = (char *)malloc(strlen(str) + 1);
    if (node->str == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->str, str);
    node->next = NULL;
    return node;
}

void free_list(ListNode *head) {
    ListNode *current = head;
    while (current != NULL) {
        ListNode *next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
}

ListNode *string_to_list(const char *input, const char *delimiter) {
    if (input == NULL || delimiter == NULL || delimiter[0] == '\0') {
        return NULL;
    }

    ListNode *head = NULL;
    ListNode *tail = NULL;

    const char *start = input;
    const char *end;
    size_t delim_len = strlen(delimiter);

    while ((end = strstr(start, delimiter)) != NULL) {
        size_t token_len = end - start;
        if (token_len > 0) {
            char *token = (char *)malloc(token_len + 1);
            if (token == NULL) {
                free_list(head);
                return NULL;
            }
            strncpy(token, start, token_len);
            token[token_len] = '\0';

            ListNode *node = create_node(token);
            free(token);
            if (node == NULL) {
                free_list(head);
                return NULL;
            }

            if (head == NULL) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
        start = end + delim_len;
    }

    if (*start != '\0') {
        ListNode *node = create_node(start);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    return head;
}

void print_list(const ListNode *head) {
    const ListNode *current = head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input_string> <delimiter>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    const char *delimiter = argv[2];

    ListNode *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}