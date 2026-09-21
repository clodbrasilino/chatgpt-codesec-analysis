#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    size_t length;
    struct Node *next;
} Node;

char *concatenate_list(Node *head) {
    size_t total_length = 0;
    Node *current = head;
    size_t offset = 0;
    char *result;

    while (current != NULL) {
        if (current->length > SIZE_MAX - total_length) {
            return NULL;
        }
        total_length += current->length;
        current = current->next;
    }

    result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    current = head;
    while (current != NULL) {
        /* Possible weaknesses found:
         *  Assuming that condition 'offset+current->length>total_length' is not redundant
         */
        if (offset + current->length > total_length) {
            free(result);
            return NULL;
        }
        if (current->length > 0) {
            /* Possible weaknesses found:
             *  Condition 'offset+current->length<=total_length' is always true
             *  Condition 'offset+current->length<=total_length' is always true [knownConditionTrueFalse]
             */
            if (offset + current->length <= total_length) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, current->data, current->length);
                offset += current->length;
            } else {
                free(result);
                return NULL;
            }
        }
        current = current->next;
    }
    result[offset] = '\0';

    return result;
}

Node *create_node(const char *str) {
    size_t len;
    Node *node;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    len = 0;
    while (str[len] != '\0') {
        if (len == SIZE_MAX) {
            return NULL;
        }
        len++;
    }

    node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->data = (char *)malloc(len + 1);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        node->data[i] = str[i];
    }
    node->length = len;
    node->next = NULL;

    return node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    char *result;

    const char *words[] = {"Hello", " ", "World", "!", NULL};
    int i;

    for (i = 0; words[i] != NULL; i++) {
        Node *node = create_node(words[i]);
        if (node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    result = concatenate_list(head);
    if (result == NULL) {
        free_list(head);
        return 1;
    }

    printf("%s\n", result);

    free(result);
    free_list(head);

    return 0;
}