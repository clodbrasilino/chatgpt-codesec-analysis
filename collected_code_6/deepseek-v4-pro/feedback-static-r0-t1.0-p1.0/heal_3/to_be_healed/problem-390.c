#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    if (str == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    new_node->data = (char*)malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_node->data, str);
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
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

int insert_at_beginning(Node **head, const char *prefix) {
    if (head == NULL || prefix == NULL) {
        return -1;
    }
    
    Node *current = *head;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(prefix);
    
    while (current != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t data_len = strlen(current->data);
        size_t new_len = prefix_len + data_len + 1;
        
        if (new_len < prefix_len || new_len < data_len) {
            return -1;
        }
        
        char *new_str = (char*)malloc(new_len);
        if (new_str == NULL) {
            return -1;
        }
        
        if (prefix_len + data_len > new_len - 1) {
            free(new_str);
            return -1;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str + prefix_len, current->data, data_len);
        new_str[new_len - 1] = '\0';
        
        free(current->data);
        current->data = new_str;
        current = current->next;
    }
    return 0;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node *list = NULL;
    Node *tail = NULL;
    const char *items[] = {"apple", "banana", "cherry"};
    size_t num_items = sizeof(items) / sizeof(items[0]);
    size_t i;

    for (i = 0; i < num_items; i++) {
        Node *new_node = create_node(items[i]);
        if (new_node == NULL) {
            free_list(list);
            return 1;
        }
        if (list == NULL) {
            list = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    printf("Original list:\n");
    print_list(list);

    if (insert_at_beginning(&list, "pre_") != 0) {
        free_list(list);
        return 1;
    }

    printf("\nModified list:\n");
    print_list(list);

    free_list(list);
    return 0;
}