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
  *  test case 0 failed: expected ['python', 'programming'], got []
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  */

Node *string_to_list(const char *str, const char *delimiter) {
    if (str == NULL || delimiter == NULL || *delimiter == '\0') {
        return NULL;
    }
    
    if (*str == '\0') {
        return NULL;
    }
    
    char *str_copy = (char *)malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        return NULL;
    }
    strcpy(str_copy, str);
    
    Node *head = NULL;
    Node *tail = NULL;
    char *saveptr;
    char *token = strtok_r(str_copy, delimiter, &saveptr);
    
    while (token != NULL) {
        if (*token != '\0') {
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
        }
        
        token = strtok_r(NULL, delimiter, &saveptr);
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
    const char *test_string1 = "apple,banana,cherry,date";
    const char *delimiter1 = ",";
    
    Node *list1 = string_to_list(test_string1, delimiter1);
    if (list1 != NULL) {
        print_list(list1);
        free_list(list1);
    }
    
    const char *test_string2 = "python programming";
    const char *delimiter2 = " ";
    
    Node *list2 = string_to_list(test_string2, delimiter2);
    if (list2 != NULL) {
        print_list(list2);
        free_list(list2);
    }
    
    const char *test_string3 = "lists,tuples,strings";
    const char *delimiter3 = ",";
    
    Node *list3 = string_to_list(test_string3, delimiter3);
    if (list3 != NULL) {
        print_list(list3);
        free_list(list3);
    }
    
    const char *test_string4 = "write,a,program";
    const char *delimiter4 = ",";
    
    Node *list4 = string_to_list(test_string4, delimiter4);
    if (list4 != NULL) {
        print_list(list4);
        free_list(list4);
    }
    
    return 0;
}