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
    
    if (!str) return NULL;
    
    len = strnlen(str, 4096);
    if (len == 0 || len >= 4096) return NULL;
    
    new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    new_node->data = (char *)malloc(len + 1);
    if (!new_node->data) {
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node *string_to_list(const char *str, const char *delimiter) {
    char *copy;
    Node *head = NULL;
    Node *tail = NULL;
    char *saveptr = NULL;
    char *token;
    size_t len;
    size_t delim_len;
    
    if (!str || !delimiter) return NULL;
    
    delim_len = strnlen(delimiter, 256);
    if (delim_len == 0 || delim_len >= 256) return NULL;
    
    len = strnlen(str, 4096);
    if (len == 0 || len >= 4096) return NULL;
    
    copy = (char *)malloc(len + 1);
    if (!copy) return NULL;
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len);
    copy[len] = '\0';
    
    token = strtok_r(copy, delimiter, &saveptr);
    while (token) {
        Node *new_node = create_node(token);
        if (!new_node) {
            Node *current = head;
            while (current) {
                Node *next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            free(copy);
            return NULL;
        }
        
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        
        token = strtok_r(NULL, delimiter, &saveptr);
    }
    
    free(copy);
    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

Node *find_node(Node *head, const char *str) {
    Node *current = head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void print_list(Node *head) {
    Node *current = head;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *str = "hello,world,example,test";
    const char *delimiter = ",";
    
    Node *list = string_to_list(str, delimiter);
    if (!list) {
        fprintf(stderr, "Error: Failed to create list\n");
        return 1;
    }
    
    print_list(list);
    free_list(list);
    
    return 0;
}