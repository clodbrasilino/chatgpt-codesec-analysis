#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    const char *data;
    struct list_node *next;
} list_node;

char *concatenate_list(const list_node *head) {
    const list_node *cur;
    size_t total = 0;
    char *result;
    char *pos;

    for (cur = head; cur != NULL; cur = cur->next) {
        size_t len;

        if (cur->data == NULL) {
            return NULL;
        }

        len = strlen(cur->data);
        if (len > SIZE_MAX - total) {
            return NULL;
        }
        total += len;
    }

    if (total == SIZE_MAX) {
        return NULL;
    }

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = result;
    for (cur = head; cur != NULL; cur = cur->next) {
        size_t len = strlen(cur->data);
        memcpy(pos, cur->data, len);
        pos += len;
    }
    *pos = '\0';

    return result;
}

int main(void) {
    list_node *n1 = malloc(sizeof(*n1));
    list_node *n2 = malloc(sizeof(*n2));
    list_node *n3 = malloc(sizeof(*n3));
    list_node *head;
    char *result;

    if (n1 == NULL || n2 == NULL || n3 == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return EXIT_FAILURE;
    }

    n1->data = "Hello";
    n1->next = n2;
    n2->data = " ";
    n2->next = n3;
    n3->data = "World";
    n3->next = NULL;
    head = n1;

    result = concatenate_list(head);
    if (result == NULL) {
        free(n1);
        free(n2);
        free(n3);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    free(n1);
    free(n2);
    free(n3);

    return EXIT_SUCCESS;
}