#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node;
    size_t len;
    char *data_copy;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, 4096);
    if (len == 4096) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    data_copy = (char *)malloc(len + 1);
    if (data_copy == NULL) {
        free(new_node);
        return NULL;
    }
    
    memcpy(data_copy, str, len);
    data_copy[len] = '\0';
    
    new_node->data = data_copy;
    new_node->next = NULL;
    return new_node;
}

Node *string_to_list(const char *str, const char *delimiter) {
    char *str_copy;
    size_t str_len;
    Node *head;
    Node *tail;
    char *saveptr;
    char *token;
    Node *new_node;
    Node *current;
    Node *next;
    
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }
    
    if (strnlen(delimiter, 256) == 0) {
        return NULL;
    }
    
    str_len = strnlen(str, 262144);
    if (str_len == 262144) {
        return NULL;
    }
    
    str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    
    memcpy(str_copy, str, str_len);
    str_copy[str_len] = '\0';
    
    head = NULL;
    tail = NULL;
    token = strtok_r(str_copy, delimiter, &saveptr);
    
    while (token != NULL) {
        new_node = create_node(token);
        if (new_node == NULL) {
            free(str_copy);
            current = head;
            while (current != NULL) {
                next = current->next;
                free(current->data);
                free(current);
                current = next;
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
    Node *current;
    Node *next;
    
    current = head;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current;
    
    current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *test_string = "python,programming";
    const char *delimiter = ",";
    Node *list;
    
    list = string_to_list(test_string, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    print_list(list);
    free_list(list);
    
    test_string = "write a program";
    delimiter = " ";
    list = string_to_list(test_string, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    print_list(list);
    free_list(list);
    
    test_string = "lists,tuples,strings";
    delimiter = ",";
    list = string_to_list(test_string, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}