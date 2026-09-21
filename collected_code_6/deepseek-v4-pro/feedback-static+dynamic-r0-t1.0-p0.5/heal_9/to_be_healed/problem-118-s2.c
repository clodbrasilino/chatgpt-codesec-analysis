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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    
    new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    data_copy = (char *)malloc(len + 1);
    if (data_copy == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(data_copy, str, len + 1);
    
    new_node->data = data_copy;
    new_node->next = NULL;
    return new_node;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  */

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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (strlen(delimiter) == 0) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    str_len = strlen(str);
    
    str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str_copy, str, str_len + 1);
    
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