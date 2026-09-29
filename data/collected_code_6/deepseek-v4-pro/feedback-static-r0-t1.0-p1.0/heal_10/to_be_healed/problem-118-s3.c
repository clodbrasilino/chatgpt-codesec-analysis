#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct ListNode {
    char *str;
    struct ListNode *next;
} ListNode;

ListNode *create_node(const char *str) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (node == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 4096);
    if (len >= 4096) {
        free(node);
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        free(node);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'alloc_size=len+1', assigned value is greater than 0
     */
    size_t alloc_size = len + 1;

    node->str = (char *)malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (node->str == NULL) {
        free(node);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'alloc_size>0' is always true [knownConditionTrueFalse]
     *  Condition 'alloc_size>0' is always true
     */
    if (alloc_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(node->str, str, len);
        node->str[len] = '\0';
    }

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
    if (input == NULL || delimiter == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 1048576);
    if (len >= 1048576) {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    size_t alloc_size = len + 1;

    char *copy = (char *)malloc(alloc_size);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, len);
    copy[len] = '\0';

    ListNode *head = NULL;
    ListNode *tail = NULL;

    char *saveptr;
    char *token = strtok_r(copy, delimiter, &saveptr);
    while (token != NULL) {
        ListNode *node = create_node(token);
        if (node == NULL) {
            free_list(head);
            free(copy);
            return NULL;
        }

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }

        token = strtok_r(NULL, delimiter, &saveptr);
    }

    free(copy);
    return head;
}

void print_list(const ListNode *head) {
    const ListNode *current = head;
    while (current != NULL) {
        printf("%s\n", current->str);
        current = current->next;
    }
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    const char *delimiter = ",";

    ListNode *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }

    print_list(list);
    free_list(list);

    return EXIT_SUCCESS;
}