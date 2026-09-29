#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, char data) {
    if (list == NULL) {
        return 0;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 1;
}

void list_destroy(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List *string_to_list(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }
    List *list = list_create();
    if (list == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        if (!list_append(list, str[i])) {
            list_destroy(list);
            return NULL;
        }
    }
    return list;
}

void list_print(const List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    const char *text = "Hello, World!";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(text);
    List *list = string_to_list(text, len);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    list_print(list);
    printf("List size: %zu\n", list->size);
    
    list_destroy(list);
    return EXIT_SUCCESS;
}