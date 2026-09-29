#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int type; // 0 for int, 1 for float
    union {
        int i;
        float f;
    } data;
    struct Node* next;
} Node;

float findMin(Node* head) {
    if(head == NULL) {
        printf("Error: List is empty");
        exit(1);
    }
  
    float min = INT_MAX;
    Node* temp = head;
  
    while(temp != NULL) {
        float val;
        if(temp->type == 0) val = (float) temp->data.i;
        else val = temp->data.f;
        
        if (val < min) min = val;
        temp = temp->next;
    }
    return min;
}

int main() {
    Node node3 = {0, {.i = 3}, NULL};
    Node node2 = {0, {.i = 2}, &node3};
    Node node1 = {1, {.f = 0.5}, &node2};
    
    printf("Minimum value: %f", findMin(&node1));
  
    return 0;
}