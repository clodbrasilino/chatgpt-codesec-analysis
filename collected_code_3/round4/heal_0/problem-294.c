#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int type; // 0 for int, 1 for float
    union {
        int i;
        float f;
    } value;
    struct Node* next;
} Node;

Node* createNode(int type, int i, float f) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->type = type;
    if (type == 0) {
        newNode->value.i = i;
    } else {
        newNode->value.f = f;
    }
    newNode->next = NULL;
    return newNode;
}

void addNode(Node** head, int type, int i, float f) {
    Node* newNode = createNode(type, i, f);
    newNode->next = *head;
    *head = newNode;
}

float findMax(Node* head) {
    float max = -1;
    while (head != NULL) {
        if (head->type == 0) {
            if (head->value.i > max) {
                max = head->value.i;
            }
        } else {
            if (head->value.f > max) {
                max = head->value.f;
            }
        }
        head = head->next;
    }
    return max;
}

int main() {
    Node* head = NULL;
    addNode(&head, 0, 5, 0);
    addNode(&head, 1, 0, 7.5);
    addNode(&head, 0, 3, 0);
    addNode(&head, 1, 0, 4.2);
    printf("Max value: %.2f\n", findMax(head));
    return 0;
}