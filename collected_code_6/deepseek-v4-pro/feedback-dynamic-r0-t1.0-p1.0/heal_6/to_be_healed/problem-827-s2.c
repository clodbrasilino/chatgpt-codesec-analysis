#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 9, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  */

int sum_column(Node *head, int column) {
    if (head == NULL || column < 0) return 0;
    
    int sum = 0;
    Node *current = head;
    
    while (current != NULL) {
        if (current->data != NULL && column < current->size) {
            sum += current->data[column];
        }
        current = current->next;
    }
    
    return sum;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {5, 6, 7};
    int arr3[] = {8, 9};
    
    Node *head = create_node(arr1, 4);
    if (head == NULL) {
        return 1;
    }
    
    Node *node2 = create_node(arr2, 3);
    if (node2 == NULL) {
        free_list(head);
        return 1;
    }
    
    Node *node3 = create_node(arr3, 2);
    if (node3 == NULL) {
        free_list(head);
        free_list(node2);
        return 1;
    }
    
    head->next = node2;
    node2->next = node3;
    
    int result = sum_column(head, 1);
    printf("%d\n", result);
    
    result = sum_column(head, 3);
    printf("%d\n", result);
    
    result = sum_column(head, 5);
    printf("%d\n", result);
    
    free_list(head);
    
    return 0;
}