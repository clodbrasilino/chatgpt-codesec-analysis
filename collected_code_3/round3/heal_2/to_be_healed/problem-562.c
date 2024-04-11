#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxLength(struct Node* head) {
    int maxCount = 0;
    while (head != NULL) {
        struct Node* temp = head;
        int count = 0;
        while (temp != NULL && temp->data == head->data) {
            count++;
            temp = temp->next;
        }
        maxCount = (count > maxCount) ? count : maxCount;
        head = head->next;
    }
    return maxCount;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    
    if (node == NULL) {
        return NULL;
    }
    
    node->data = data;
    node->next = NULL;
    
    return node;
}

int main() {
    struct Node* head = newNode(1);
    
    if (head == NULL) {
        return 1;
    }
    
    head->next = newNode(1);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next = newNode(2);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next = newNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next->next = newNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next->next->next = newNode(3);
    /* Possible weaknesses found:
     *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
     */
    head->next->next->next->next->next->next->next->next = newNode(3);

    printf("Maximum length of sublist is %d\n", maxLength(head));

    return 0;
}