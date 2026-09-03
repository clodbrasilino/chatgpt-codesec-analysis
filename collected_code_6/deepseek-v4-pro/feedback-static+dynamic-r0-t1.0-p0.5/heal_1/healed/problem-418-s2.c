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

Node *append_node(Node *head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return NULL;
    }
    
    if (head == NULL) {
        return new_node;
    }
    
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

int list_length(Node *head) {
    int count = 0;
    Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Sublist find_max_sublist(Node *head) {
    Sublist result;
    result.head = NULL;
    result.length = 0;
    
    if (head == NULL) {
        return result;
    }
    
    Node *max_start = head;
    Node *max_end = head;
    int max_length = 1;
    
    Node *temp_start = head;
    Node *temp_end = head;
    int temp_length = 1;
    
    Node *current = head->next;
    
    while (current != NULL) {
        if (current->data >= temp_end->data) {
            temp_end = current;
            temp_length++;
        } else {
            if (temp_length > max_length) {
                max_length = temp_length;
                max_start = temp_start;
                max_end = temp_end;
            }
            temp_start = current;
            temp_end = current;
            temp_length = 1;
        }
        current = current->next;
    }
    
    if (temp_length > max_length) {
        max_length = temp_length;
        max_start = temp_start;
        max_end = temp_end;
    }
    
    Node *result_head = NULL;
    Node *result_tail = NULL;
    Node *iter = max_start;
    
    while (iter != max_end->next) {
        Node *new_node = create_node(iter->data);
        if (new_node == NULL) {
            free_list(result_head);
            result.head = NULL;
            result.length = 0;
            return result;
        }
        
        if (result_head == NULL) {
            result_head = new_node;
            result_tail = new_node;
        } else {
            result_tail->next = new_node;
            result_tail = new_node;
        }
        iter = iter->next;
    }
    
    result.head = result_head;
    result.length = max_length;
    return result;
}

int main(void) {
    Node *list = NULL;
    int values[] = {1, 2, 3, 2, 4, 5, 6, 1, 2, 3, 4, 5};
    int n = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < n; i++) {
        list = append_node(list, values[i]);
        if (list == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }
    
    Sublist max_sublist = find_max_sublist(list);
    
    printf("Maximum sublist length: %d\n", max_sublist.length);
    printf("Maximum sublist: ");
    
    Node *current = max_sublist.head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    
    free_list(list);
    free_list(max_sublist.head);
    
    return 0;
}