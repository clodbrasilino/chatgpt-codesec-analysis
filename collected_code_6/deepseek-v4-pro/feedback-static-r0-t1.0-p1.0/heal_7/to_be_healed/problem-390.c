#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *str) {
    Node *new_node;
    size_t len;
    char *data_copy;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, SIZE_MAX);
    if (len == SIZE_MAX) {
        return NULL;
    }
    
    new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    data_copy = (char*)malloc(len + 1);
    if (data_copy == NULL) {
        free(new_node);
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(data_copy, str, len);
    }
    data_copy[len] = '\0';
    new_node->data = data_copy;
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
    Node *current;
    size_t prefix_len;
    
    if (head == NULL || prefix == NULL) {
        return -1;
    }
    
    prefix_len = strnlen(prefix, SIZE_MAX);
    if (prefix_len == SIZE_MAX) {
        return -1;
    }
    
    current = *head;
    while (current != NULL) {
        size_t data_len = strnlen(current->data, SIZE_MAX);
        size_t new_len;
        char *new_str;
        
        if (data_len == SIZE_MAX) {
            return -1;
        }
        
        if (data_len > SIZE_MAX - prefix_len) {
            return -1;
        }
        
        new_len = prefix_len + data_len;
        if (new_len > SIZE_MAX - 1) {
            return -1;
        }
        
        new_len += 1;
        
        new_str = (char*)malloc(new_len);
        if (new_str == NULL) {
            return -1;
        }
        
        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_str, prefix, prefix_len);
        }
        if (data_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(new_str + prefix_len, current->data, data_len);
        }
        new_str[prefix_len + data_len] = '\0';
        
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