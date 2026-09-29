#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    if (str == NULL) {
        new_node->data = NULL;
        new_node->next = NULL;
        return new_node;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    
    if (len >= SIZE_MAX) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     */
    if (alloc_size <= len) {
        free(new_node);
        return NULL;
    }
    
    new_node->data = (char *)malloc(alloc_size);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->data, str, len);
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
}

Node *string_to_list(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    
    if (len >= SIZE_MAX) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     */
    if (alloc_size <= len) {
        return NULL;
    }
    
    char *str_copy = (char *)malloc(alloc_size);
    if (str_copy == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str_copy, str, len);
    str_copy[len] = '\0';
    
    Node *head = NULL;
    Node *tail = NULL;
    char *saveptr;
    char *token = strtok_r(str_copy, delimiter, &saveptr);
    
    while (token != NULL) {
        Node *new_node = create_node(token);
        if (new_node == NULL) {
            free(str_copy);
            Node *current = head;
            while (current != NULL) {
                Node *temp = current;
                current = current->next;
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
        if (current->data != NULL) {
            printf("%s\n", current->data);
        }
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