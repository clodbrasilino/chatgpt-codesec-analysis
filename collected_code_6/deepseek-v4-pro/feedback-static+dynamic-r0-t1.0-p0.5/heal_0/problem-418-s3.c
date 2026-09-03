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

Node *copy_list(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    
    Node *new_head = create_node(head->data);
    if (new_head == NULL) {
        return NULL;
    }
    
    Node *current_orig = head->next;
    Node *current_new = new_head;
    
    while (current_orig != NULL) {
        current_new->next = create_node(current_orig->data);
        if (current_new->next == NULL) {
            free_list(new_head);
            return NULL;
        }
        current_new = current_new->next;
        current_orig = current_orig->next;
    }
    
    return new_head;
}

Sublist find_max_sublist(Node *head) {
    Sublist result;
    result.head = NULL;
    result.length = 0;
    
    if (head == NULL) {
        return result;
    }
    
    Node *current = head;
    int current_length = 1;
    Node *current_start = head;
    
    int max_length = 1;
    Node *max_start = head;
    
    while (current->next != NULL) {
        if (current->next->data >= current->data) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
            }
            current_start = current->next;
            current_length = 1;
        }
        current = current->next;
    }
    
    if (current_length > max_length) {
        max_length = current_length;
        max_start = current_start;
    }
    
    result.head = copy_list(max_start);
    if (result.head == NULL) {
        result.length = 0;
        return result;
    }
    
    result.length = max_length;
    
    Node *temp = result.head;
    for (int i = 0; i < max_length - 1; i++) {
        temp = temp->next;
    }
    temp->next = NULL;
    
    return result;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 5, 6, 7, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Node *head = NULL;
    Node *tail = NULL;
    
    for (int i = 0; i < n; i++) {
        Node *new_node = create_node(arr[i]);
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
    
    printf("Original list: ");
    print_list(head);
    
    Sublist result = find_max_sublist(head);
    
    printf("Maximum sublist (length %d): ", result.length);
    print_list(result.head);
    
    free_list(result.head);
    free_list(head);
    
    return 0;
}