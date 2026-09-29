#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int type; // 0 for int, 1 for float
    union {
        int i;
        float f;
    } data;
    struct node* next;
} Node;

Node* createNode(int type, int i, float f) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->type = type;
    if (type == 0) {
        newNode->data.i = i;
    } else {
        newNode->data.f = f;
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
    float max = -1.0f;
    while (head != NULL) {
        if (head->type == 0) {
            if (head->data.i > max) {
                max = head->data.i;
            }
        } else {
            if (head->data.f > max) {
                max = head->data.f;
            }
        }
        head = head->next;
    }
    return max;
}

int main() {
    Node* head = NULL;
    addNode(&head, 0, 5, 0.0f);
    addNode(&head, 1, 0, 2.5f);
    addNode(&head, 0, 3, 0.0f);
    addNode(&head, 1, 0, 7.1f);
    printf("Max value: %.2f\n", findMax(head));
    return 0;
}