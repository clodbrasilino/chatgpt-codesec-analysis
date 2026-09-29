#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node;
    size_t len;
    size_t alloc_size;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, SIZE_MAX);
    alloc_size = len + 1;
    
    if (alloc_size <= len) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = (char *)malloc(alloc_size);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    memcpy(new_node->data, str, len);
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
}

Node *string_to_list(const char *str, const char *delimiter) {
    size_t len;
    char *str_copy;
    Node *head;
    Node *tail;
    char *saveptr;
    char *token;
    
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }
    
    len = strnlen(str, SIZE_MAX);
    str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    
    memcpy(str_copy, str, len);
    str_copy[len] = '\0';
    
    head = NULL;
    tail = NULL;
    token = strtok_r(str_copy, delimiter, &saveptr);
    
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free(str_copy);
            while (head != NULL) {
                Node *temp = head;
                head = head->next;
                free(temp->data);
                free(temp);
            }
            return NULL;
        }
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        
        token = strtok_r(NULL, delimiter, &saveptr);
    }
    
    free(str_copy);
    return head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

void print_list(Node *head) {
    while (head != NULL) {
        printf("%s\n", head->data);
        head = head->next;
    }
}

int main(void) {
    const char *test_string = "apple,banana,cherry,date";
    const char *delimiter = ",";
    
    Node *list = string_to_list(test_string, delimiter);
    
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}