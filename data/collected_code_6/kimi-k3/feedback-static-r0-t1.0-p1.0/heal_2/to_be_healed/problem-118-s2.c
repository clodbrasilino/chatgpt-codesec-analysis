#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *data, size_t data_len) {
    if (data == NULL) {
        return NULL;
    }
    
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = (char*)malloc(data_len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->data, data, data_len);
    new_node->data[data_len] = '\0';
    new_node->next = NULL;
    return new_node;
}

Node* string_to_list(const char *str, size_t str_len, const char *delim, size_t delim_len) {
    if (str == NULL || delim == NULL || delim_len == 0) {
        return NULL;
    }
    
    char *str_copy = (char*)malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str_copy, str, str_len);
    str_copy[str_len] = '\0';
    
    Node *head = NULL;
    Node *tail = NULL;
    size_t pos = 0;
    
    while (pos <= str_len) {
        size_t token_start = pos;
        size_t token_len = 0;
        
        while (pos < str_len) {
            int is_delim = 0;
            for (size_t i = 0; i < delim_len; i++) {
                if (str_copy[pos] == delim[i]) {
                    is_delim = 1;
                    break;
                }
            }
            if (is_delim) {
                break;
            }
            pos++;
            token_len++;
        }
        
        if (token_len > 0) {
            Node *new_node = create_node(str_copy + token_start, token_len);
            if (new_node == NULL) {
                while (head != NULL) {
                    Node *temp = head;
                    head = head->next;
                    free(temp->data);
                    free(temp);
                }
                free(str_copy);
                return NULL;
            }
            
            if (head == NULL) {
                head = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        
        if (pos < str_len) {
            pos++;
        } else {
            break;
        }
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
    Node *current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    const char *input = "apple,banana,cherry,date";
    const char *delimiter = ",";
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    Node *list = string_to_list(input, strlen(input), delimiter, strlen(delimiter));
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}