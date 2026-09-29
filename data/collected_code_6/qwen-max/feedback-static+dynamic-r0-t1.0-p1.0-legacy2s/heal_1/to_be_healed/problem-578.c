#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int length(Node *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

Node* interleaveLists(Node *first, Node *second) {
    if (first == NULL || second == NULL) {
        return first ? first : second;
    }

    Node *result = NULL;
    Node **ptr = &result;

    while (first && second) {
        *ptr = first;
        first = first->next;
        ptr = &(*ptr)->next;

        *ptr = second;
        second = second->next;
        ptr = &(*ptr)->next;
    }

    *ptr = (first ? first : second);

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
Node* createList(int arr[], int n) {
    Node *head = NULL;
    Node **ptr = &head;
    for (int i = 0; i < n; i++) {
        *ptr = createNode(arr[i]);
        ptr = &(*ptr)->next;
    }
    return head;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

void freeList(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int arr1[] = {1, 3, 5};
    int arr2[] = {2, 4, 6};
    /* Possible weaknesses found:
     *  Assignment 'n1=sizeof(arr1)/sizeof(arr1[0])', assigned value is 3
     */
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    /* Possible weaknesses found:
     *  Condition 'n1!=n2' is always false [knownConditionTrueFalse]
     *  Condition 'n1!=n2' is always false
     */
    if (n1 != n2) {
        return 1;
    }

    Node *list1 = createList(arr1, n1);
    Node *list2 = createList(arr2, n2);

    Node *result = interleaveLists(list1, list2);

    printList(result);

    freeList(result);

    return 0;
}