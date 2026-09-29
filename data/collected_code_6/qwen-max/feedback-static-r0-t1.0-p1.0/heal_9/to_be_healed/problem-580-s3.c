#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Tuple {
    int type; 
    union {
        int intValue;
        struct Tuple *tupleValue;
    };
    struct Tuple *next;
} Tuple;

Node* extractEvenElements(Tuple *t) {
    Node *head = NULL;
    Node *current = NULL;

    if (t->type == 1 && t->intValue % 2 == 0) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->value = t->intValue;
        newNode->next = NULL;
        head = newNode;
        /* Possible weaknesses found:
         *  Variable 'current' is assigned a value that is never used. [unreadVariable]
         */
        current = head;
    } else if (t->type == 2) {
        Tuple *nestedTuple = t->tupleValue;
        while (nestedTuple != NULL) {
            if (nestedTuple->type == 1 && nestedTuple->intValue % 2 == 0) {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->value = nestedTuple->intValue;
                newNode->next = NULL;
                if (head == NULL) {
                    head = newNode;
                    current = head;
                } else {
                    current->next = newNode;
                    current = newNode;
                }
            } else if (nestedTuple->type == 2) {
                Node *newNode = extractEvenElements(nestedTuple);
                if (newNode != NULL) {
                    if (head == NULL) {
                        head = newNode;
                        current = head;
                    } else {
                        current->next = newNode;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                    }
                }
            }
            nestedTuple = nestedTuple->next;
        }
    }
    return head;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
}

int main() {
    Tuple *t1 = (Tuple*)malloc(sizeof(Tuple));
    t1->type = 1;
    t1->intValue = 2;

    Tuple *t2 = (Tuple*)malloc(sizeof(Tuple));
    t2->type = 1;
    t2->intValue = 3;

    Tuple *t3 = (Tuple*)malloc(sizeof(Tuple));
    t3->type = 1;
    t3->intValue = 4;

    Tuple *t4 = (Tuple*)malloc(sizeof(Tuple));
    t4->type = 2;
    t4->tupleValue = t1;
    t4->next = NULL;

    Tuple *t5 = (Tuple*)malloc(sizeof(Tuple));
    t5->type = 2;
    t5->tupleValue = t2;
    t5->next = NULL;

    Tuple *t6 = (Tuple*)malloc(sizeof(Tuple));
    t6->type = 2;
    t6->tupleValue = t3;
    t6->next = NULL;

    t4->next = t5;
    t5->next = t6;
    t6->next = NULL;

    Node *result = extractEvenElements(t4);
    printList(result);
    freeList(result);

    free(t1);
    free(t2);
    free(t3);
    free(t4);
    free(t5);
    free(t6);

    return 0;
}