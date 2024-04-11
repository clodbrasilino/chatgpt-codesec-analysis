#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int type; 
    union {
        int i;
        float f;
    } value;
    struct Node* next;
} Node;

Node* createNode(int type, int i, float f) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->type = type;
    
    if (type == 0) {
        node->value.i = i;
    } else {
        node->value.f = f;
    }
    node->next = NULL;

    return node;
}

float findMin(Node* head) {

    if (!head) {
        return 0;
    }

    float min = (head->type == 0) ? (float)head->value.i : head->value.f;
    Node* temp = head->next;

    while (temp != NULL) {

        if (temp->type == 0 && temp->value.i < min) {
            min = (float)temp->value.i;
        } 
        else if (temp->type == 1 && temp->value.f < min) {
            min = temp->value.f;
        }

        temp = temp->next;
    }
    return min;
}
      
int main() {
    Node* head = createNode(0, 5, 0.0f);
    if(head == NULL){
        return -1;
    }

    head->next = createNode(1, 0, 3.5f);
    if(head->next == NULL){
        return -1;
    }

    head->next->next = createNode(0, 2, 0.0f);
    if(head->next->next == NULL){
        return -1;
    }

    head->next->next->next = createNode(1, 0, 1.2f);
    if(head->next->next->next == NULL){
        return -1;
    }

    printf("Minimum value: %.2f\n", findMin(head));
    return 0;
}