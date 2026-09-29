#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node *create_node(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data, str);
    new_node->next = NULL;
    return new_node;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  */

Node *string_to_list(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL || strlen(delimiter) == 0) {
        return NULL;
    }
    
    size_t str_len = strlen(str);
    char *str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    memcpy(str_copy, str, str_len + 1);
    
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
                Node *next = current->next;
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
    
    if (head == NULL) {
        char *remaining = str_copy;
        while (*remaining != '\0' && strchr(delimiter, *remaining) != NULL) {
            remaining++;
        }
        if (*remaining == '\0') {
            free(str_copy);
            return NULL;
        }
    }
    
    free(str_copy);
    return head;
}

Node *string_to_list_fixed(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL || strlen(delimiter) == 0) {
        return NULL;
    }
    
    size_t str_len = strlen(str);
    char *str_copy = (char *)malloc(str_len + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    memcpy(str_copy, str, str_len + 1);
    
    Node *head = NULL;
    Node *tail = NULL;
    /* Possible weaknesses found:
     *  Variable 'saveptr' can be declared as pointer to const [constVariablePointer]
     *  Variable 'saveptr' is assigned a value that is never used. [unreadVariable]
     */
    char *saveptr = NULL;
    /* Possible weaknesses found:
     *  Variable 'token' can be declared as pointer to const [constVariablePointer]
     *  Variable 'token' is assigned a value that is never used. [unreadVariable]
     */
    char *token = NULL;
    
    size_t delim_len = strlen(delimiter);
    char *input = str_copy;
    char *next_token = strstr(input, delimiter);
    
    while (next_token != NULL || *input != '\0') {
        size_t token_len;
        /* Possible weaknesses found:
         *  The scope of the variable 'token_start' can be reduced. [variableScope]
         */
        char *token_start;
        
        if (next_token != NULL) {
            token_len = next_token - input;
            if (token_len > 0) {
                token_start = input;
                char *temp_token = (char *)malloc(token_len + 1);
                if (temp_token == NULL) {
                    free(str_copy);
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
                    return NULL;
                }
                memcpy(temp_token, token_start, token_len);
                temp_token[token_len] = '\0';
                
                Node *new_node = create_node(temp_token);
                free(temp_token);
                
                if (new_node == NULL) {
                    free(str_copy);
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
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
            }
            input = next_token + delim_len;
            next_token = strstr(input, delimiter);
        } else {
            token_len = strlen(input);
            if (token_len > 0) {
                Node *new_node = create_node(input);
                if (new_node == NULL) {
                    free(str_copy);
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
                    return NULL;
                }
                
                if (head == NULL) {
                    head = new_node;
                    /* Possible weaknesses found:
                     *  Value stored to 'tail' is never read [deadcode.DeadStores]
                     *  Variable 'tail' is assigned a value that is never used. [unreadVariable]
                     */
                    tail = new_node;
                } else {
                    tail->next = new_node;
                    /* Possible weaknesses found:
                     *  Value stored to 'tail' is never read [deadcode.DeadStores]
                     *  Variable 'tail' is assigned a value that is never used. [unreadVariable]
                     */
                    tail = new_node;
                }
            }
            break;
        }
    }
    
    free(str_copy);
    return head;
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
    const char *test_string1 = "python programming";
    const char *delimiter1 = " ";
    
    Node *list1 = string_to_list_fixed(test_string1, delimiter1);
    if (list1 != NULL) {
        print_list(list1);
        free_list(list1);
    }
    
    const char *test_string2 = "write a program";
    const char *delimiter2 = " ";
    
    Node *list2 = string_to_list_fixed(test_string2, delimiter2);
    if (list2 != NULL) {
        print_list(list2);
        free_list(list2);
    }
    
    const char *test_string3 = "lists,tuples,strings";
    const char *delimiter3 = ",";
    
    Node *list3 = string_to_list_fixed(test_string3, delimiter3);
    if (list3 != NULL) {
        print_list(list3);
        free_list(list3);
    }
    
    return EXIT_SUCCESS;
}