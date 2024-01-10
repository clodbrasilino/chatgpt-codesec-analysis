#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int value) {
    if (*head == NULL) {
        *head = createNode(value);
    } else {
        Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = createNode(value);
    }
}

void displayList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

Node* convertToList(int* arr, int size) {
    Node* head = NULL;
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        insertNode(&head, arr[i]);
    }
    return head;
}

void convertToTuple(Node* head, int** tuple, int* size) {
    Node* curr = head;
    *size = 0;
    while (curr != NULL) {
        (*size)++;
        curr = curr->next;
    }
    *tuple = (int*)malloc(*size * sizeof(int));
    curr = head;
    for (int i = 0; i < *size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        (*tuple)[i] = curr->data;
        curr = curr->next;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    Node* head = convertToList(arr, size);

    int* tuple;
    int tupleSize;
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleSize' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'tuple' is initialized [premium-bughuntingUninit]
     */
    convertToTuple(head, &tuple, &tupleSize);

    printf("Tuple: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'tupleSize' is initialized [premium-bughuntingUninit]
     */
    for (int i = 0; i < tupleSize; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'tuple' is initialized [premium-bughuntingUninit]
         */
        printf("%d ", tuple[i]);
    }
    printf("\n");

    /* Possible weaknesses found:
     *  Cannot determine that 'tuple' is initialized [premium-bughuntingUninit]
     */
    free(tuple);
    return 0;
}