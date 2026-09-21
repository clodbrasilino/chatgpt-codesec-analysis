#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node = NULL;
    char *data = NULL;
    size_t len;
    const char *p;
    
    if (str == NULL) {
        return NULL;
    }
    
    p = str;
    len = 0;
    while (len < SIZE_MAX && *p != '\0') {
        len++;
        p++;
    }
    
    if (len == SIZE_MAX) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    if (len > SIZE_MAX - 1) {
        free(new_node);
        return NULL;
    }
    
    data = (char *)malloc(len + 1);
    if (data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(data, str, len);
    data[len] = '\0';
    
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_beginning(Node **head, const char *str) {
    Node *new_node;
    
    if (head == NULL) {
        return;
    }
    
    new_node = create_node(str);
    if (new_node == NULL) {
        return;
    }
    
    new_node->next = *head;
    *head = new_node;
}

void prepend_to_all(Node *head, const char *prefix) {
    Node *current;
    size_t prefix_len;
    const char *p;
    
    if (prefix == NULL) {
        return;
    }
    
    p = prefix;
    prefix_len = 0;
    while (prefix_len < SIZE_MAX && *p != '\0') {
        prefix_len++;
        p++;
    }
    
    if (prefix_len == SIZE_MAX) {
        return;
    }
    
    current = head;
    
    while (current != NULL) {
        size_t data_len;
        const char *q;
        size_t new_len;
        char *new_str;
        
        q = current->data;
        data_len = 0;
        while (data_len < SIZE_MAX && *q != '\0') {
            data_len++;
            q++;
        }
        
        if (data_len == SIZE_MAX) {
            return;
        }
        
        if (prefix_len > SIZE_MAX - data_len) {
            return;
        }
        
        if (prefix_len + data_len > SIZE_MAX - 1) {
            return;
        }
        
        new_len = prefix_len + data_len + 1;
        
        new_str = (char *)malloc(new_len);
        if (new_str == NULL) {
            return;
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

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node *list = NULL;
    
    insert_at_beginning(&list, "world");
    insert_at_beginning(&list, "there");
    insert_at_beginning(&list, "hello");
    
    printf("Original list:\n");
    print_list(list);
    
    prepend_to_all(list, "say_");
    
    printf("\nModified list:\n");
    print_list(list);
    
    free_list(list);
    
    return 0;
}