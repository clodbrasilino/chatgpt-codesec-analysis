#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node;
    char *data;
    size_t len;
    
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len >= 1024) {
        return NULL;
    }
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
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

Node *string_to_list(const char *str, const char *delimiter) {
    char *str_copy;
    Node *head;
    Node *tail;
    char *saveptr;
    char *token;
    size_t len;
    
    if (str == NULL || delimiter == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len >= 1048576) {
        return NULL;
    }
    
    str_copy = (char *)malloc(len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
                Node *next = head->next;
                free(head->data);
                free(head);
                head = next;
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
        Node *next = head->next;
        free(head->data);
        free(head);
        head = next;
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
        return 1;
    }
    
    print_list(list);
    free_list(list);
    
    return 0;
}