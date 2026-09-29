#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* create_node(char* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = (char*)malloc((strlen(data) + 1) * sizeof(char));
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strcpy(new_node->data, data);
    new_node->next = NULL;
    return new_node;
}

void delete_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got []
  *  test case 2 failed: expected ['write', 'a', 'program'], got []
  *  test case 0 failed: expected ['python', 'programming'], got []
  */

Node* string_to_list(const char* str, const char* delimiter) {
    char *token, *copy;
    Node* head = NULL;
    Node* tail = NULL;
    
    copy = strdup(str);
    if (copy == NULL) {
        return NULL;
    }
    
    token = strtok(copy, delimiter);
    while (token != NULL) {
        Node* new_node = create_node(token);
        if (new_node == NULL) {
            delete_list(head);
            free(copy);
            return NULL;
        }
        
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        
        token = strtok(NULL, delimiter);
    }
    
    free(copy);
    return head;
}

int main() {
    const char* input = "apple,banana,cherry";
    const char* delimiter = ",";
    Node* list = string_to_list(input, delimiter);
    
    if (list == NULL) {
        printf("Failed to convert string to list\n");
        return 1;
    }
    
    Node* current = list;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
    
    delete_list(list);
    return 0;
}