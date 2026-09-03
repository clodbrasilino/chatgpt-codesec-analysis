#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int length;
} Sublist;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Sublist find_max_sublist(Node *head) {
    Sublist result = {NULL, 0};
    
    if (head == NULL) {
        return result;
    }
    
    /* Possible weaknesses found:
     *  current is initialized
     */
    Node *current = head;
    Node *max_start = head;
    /* Possible weaknesses found:
     *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
     */
    Node *max_end = head;
    int max_length = 1;
    
    Node *temp_start = head;
    Node *temp_end = head;
    int temp_length = 1;
    
    /* Possible weaknesses found:
     *  current is overwritten
     *  Redundant initialization for 'current'. The initialized value is overwritten before it is read. [redundantInitialization]
     */
    current = head->next;
    
    while (current != NULL) {
        if (current->data == temp_end->data + 1) {
            temp_end = current;
            temp_length++;
        } else {
            if (temp_length > max_length) {
                max_start = temp_start;
                /* Possible weaknesses found:
                 *  Value stored to 'max_end' is never read [deadcode.DeadStores]
                 *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
                 */
                max_end = temp_end;
                max_length = temp_length;
            }
            temp_start = current;
            temp_end = current;
            temp_length = 1;
        }
        current = current->next;
    }
    
    if (temp_length > max_length) {
        max_start = temp_start;
        /* Possible weaknesses found:
         *  Value stored to 'max_end' is never read [deadcode.DeadStores]
         *  Variable 'max_end' is assigned a value that is never used. [unreadVariable]
         */
        max_end = temp_end;
        max_length = temp_length;
    }
    
    result.head = max_start;
    result.length = max_length;
    
    return result;
}

int main(void) {
    int test_data[] = {1, 2, 3, 5, 6, 7, 8, 10, 11};
    int n = sizeof(test_data) / sizeof(test_data[0]);
    
    Node *head = NULL;
    Node *tail = NULL;
    
    for (int i = 0; i < n; i++) {
        Node *new_node = create_node(test_data[i]);
        if (new_node == NULL) {
            free_list(head);
            return 1;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    
    Sublist result = find_max_sublist(head);
    
    printf("Maximum sublist length: %d\n", result.length);
    printf("Sublist elements: ");
    
    Node *current = result.head;
    for (int i = 0; i < result.length && current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    free_list(head);
    
    return 0;
}