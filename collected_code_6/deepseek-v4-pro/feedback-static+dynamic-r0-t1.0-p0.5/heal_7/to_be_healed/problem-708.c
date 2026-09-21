#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

void free_list(Node *head);

Node *create_node(const char *str) {
    Node *new_node;
    char *data_copy;
    size_t len;
    
    if (str == NULL) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    len = strnlen(str, 4096);
    if (len == 4096) {
        free(new_node);
        return NULL;
    }
    
    data_copy = (char *)malloc(len + 1);
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

Node *string_to_list(const char *str, const char *delimiter) {
    Node *head = NULL;
    Node *tail = NULL;
    char *str_copy = NULL;
    char *saveptr = NULL;
    char *token;
    size_t len;
    
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }
    
    len = strnlen(str, 4096);
    if (len == 4096) {
        return NULL;
    }
    
    str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str_copy, str, len);
    }
    str_copy[len] = '\0';
    
    token = strtok_r(str_copy, delimiter, &saveptr);
    
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free(str_copy);
            free_list(head);
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
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
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
    const char *input = "apple,banana,cherry,date";
    const char *delimiter = ",";
    
    Node *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}