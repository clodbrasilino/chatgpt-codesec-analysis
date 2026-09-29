#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

Node* create_node(const char *data) {
    if (data == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    const char *p = data;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (p[len] != '\0' && len < 4096) {
        len++;
    }
    if (p[len] != '\0') {
        return NULL;
    }
    
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    
    new_node->data = (char*)malloc(len + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(new_node->data, data, len);
    new_node->data[len] = '\0';
    new_node->next = NULL;
    return new_node;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  */

Node* string_to_list(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    const char *p = str;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     *  Assuming that condition 'len<65536' is not redundant
     */
    while (p[len] != '\0' && len < 65536) {
        len++;
    }
    /* Possible weaknesses found:
     *  Either the condition 'len<65536' is redundant or the array 'p[25]' is accessed at index 65536, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Array index out of bounds
     */
    if (p[len] != '\0') {
        return NULL;
    }
    
    char *str_copy = (char*)malloc(len + 1);
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
    char *token = strtok(str_copy, delim);
    
    while (token != NULL) {
        Node *new_node = create_node(token);
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
        
        token = strtok(NULL, delim);
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
    
    Node *list = string_to_list(input, delimiter);
    if (list == NULL) {
        fprintf(stderr, "Failed to convert string to list\n");
        return EXIT_FAILURE;
    }
    
    print_list(list);
    free_list(list);
    
    return EXIT_SUCCESS;
}