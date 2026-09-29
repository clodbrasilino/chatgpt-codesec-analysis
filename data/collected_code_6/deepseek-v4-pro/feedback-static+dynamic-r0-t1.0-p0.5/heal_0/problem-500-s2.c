#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

char *concatenate_list(Node *head) {
    if (head == NULL) {
        char *empty = (char *)malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t total_length = 0;
    Node *current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            total_length += strlen(current->data);
        }
        current = current->next;
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    current = head;
    while (current != NULL) {
        if (current->data != NULL) {
            strcat(result, current->data);
        }
        current = current->next;
    }

    return result;
}

int main(void) {
    Node node3 = {"world", NULL};
    Node node2 = {" ", &node3};
    Node node1 = {"Hello", &node2};

    char *result = concatenate_list(&node1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    Node *empty_list = NULL;
    char *empty_result = concatenate_list(empty_list);
    if (empty_result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Empty: '%s'\n", empty_result);
    free(empty_result);

    return 0;
}