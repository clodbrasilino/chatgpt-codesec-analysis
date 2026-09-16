#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int *data;
    int size;
    struct Node *next;
} Node;

Node *create_node(int *data, int size) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        free(data);
        return NULL;
    }
    node->data = data;
    node->size = size;
    node->next = NULL;
    return node;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 9, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  *  test case 1 failed: expected 15, got <no output>
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
    int *arr1 = (int *)malloc(4 * sizeof(int));
    int *arr2 = (int *)malloc(3 * sizeof(int));
    int *arr3 = (int *)malloc(2 * sizeof(int));
    
    if (arr1 == NULL || arr2 == NULL || arr3 == NULL) {
        free(arr1);
        free(arr2);
        free(arr3);
        return 1;
    }
    
    arr1[0] = 1; arr1[1] = 2; arr1[2] = 3; arr1[3] = 4;
    arr2[0] = 5; arr2[1] = 6; arr2[2] = 7;
    arr3[0] = 8; arr3[1] = 9;
    
    Node *head = create_node(arr1, 4);
    if (head == NULL) {
        free(arr2);
        free(arr3);
        return 1;
    }
    
    Node *node2 = create_node(arr2, 3);
    if (node2 == NULL) {
        free(arr3);
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
    
    int result = sum_column(head, 0);
    printf("Sum of column 0: %d\n", result);
    
    result = sum_column(head, 1);
    printf("Sum of column 1: %d\n", result);
    
    result = sum_column(head, 2);
    printf("Sum of column 2: %d\n", result);
    
    result = sum_column(head, 3);
    printf("Sum of column 3: %d\n", result);
    
    result = sum_column(head, 5);
    printf("Sum of column 5: %d\n", result);
    
    free_list(head);
    
    return 0;
}