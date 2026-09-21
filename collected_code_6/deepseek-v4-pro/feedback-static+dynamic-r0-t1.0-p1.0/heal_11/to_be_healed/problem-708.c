#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    size_t size;
} StringList;

void list_free(StringList *list);

Node *create_node(const char *str) {
    Node *new_node;
    size_t len;
    
    if (str == NULL) return NULL;
    
    len = strnlen(str, 4096);
    if (len == 4096 && str[4095] != '\0') {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    new_node->data = (char *)malloc(len + 1);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_node->data, str, len);
    }
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
}

void list_init(StringList *list) {
    if (list == NULL) return;
    list->head = NULL;
    list->size = 0;
}

int list_add(StringList *list, const char *str) {
    Node *new_node;
    
    if (list == NULL) return -1;
    
    new_node = create_node(str);
    if (!new_node) return -1;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
    return 0;
}

StringList *string_to_list(const char *str) {
    StringList *list;
    char *copy;
    char *token;
    char *saveptr;
    size_t len;
    
    list = (StringList *)malloc(sizeof(StringList));
    if (!list) return NULL;
    
    list_init(list);
    
    if (str == NULL) {
        return list;
    }
    
    len = strnlen(str, 4096);
    if (len == 4096 && str[4095] != '\0') {
        free(list);
        return NULL;
    }
    
    copy = (char *)malloc(len + 1);
    if (!copy) {
        free(list);
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, str, len);
    }
    copy[len] = '\0';
    
    token = strtok_r(copy, " \t\n\r", &saveptr);
    while (token != NULL) {
        if (list_add(list, token) != 0) {
            free(copy);
            list_free(list);
            free(list);
            return NULL;
        }
        token = strtok_r(NULL, " \t\n\r", &saveptr);
    }
    
    free(copy);
    return list;
}

void list_free(StringList *list) {
    Node *current;
    Node *next;
    
    if (list == NULL) return;
    
    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->size = 0;
}

void list_print(const StringList *list) {
    Node *current;
    
    if (list == NULL) return;
    
    current = list->head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *test_string = "hello world from C";
    StringList *list = string_to_list(test_string);
    
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }
    
    printf("String list (%zu items):\n", list->size);
    list_print(list);
    
    list_free(list);
    free(list);
    
    return EXIT_SUCCESS;
}