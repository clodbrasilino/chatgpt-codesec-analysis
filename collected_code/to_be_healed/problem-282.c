#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

struct Node {
    int data;
    struct Node* next;
};

void subtractLists(struct Node* list1, struct Node* list2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    struct Node* temp2 = NULL;

    while (list1 != NULL) {
        int exist = 0;
        temp = list2;
        while (temp != NULL) {
            if (list1->data == temp->data) {
                exist = 1;
                break;
            }
            temp = temp->next;
        }
        if (exist == 0) {
            // Add the current node to the result list
            /* Possible weaknesses found:
             *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
             *  include '<stdlib.h>' or provide a declaration of 'malloc'
             *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
             */
            struct Node* node = (struct Node*)malloc(sizeof(struct Node));
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            node->data = list1->data;
            node->next = NULL;
            if (result == NULL) {
                result = node;
            } else {
                temp2 = result;
                while (temp2->next != NULL) {
                    temp2 = temp2->next;
                }
                temp2->next = node;
            }
        }
        list1 = list1->next;
    }

    // Print the result list
    temp = result;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
/* Possible weaknesses found:
 *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    
    // Initialize list1
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     */
    list1 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list1' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list1->data = 1;
    list1->next = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list1.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list1->next->data = 2;
    list1->next->next = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list1_21->next.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list1->next->next->data = 3;
    list1->next->next->next = NULL;

    // Initialize list2
    list2 = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list2' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list2->data = 2;
    list2->next = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list2.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list2->next->data = 3;
    list2->next->next = (struct Node*)malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*list2_31->next.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list2->next->next->data = 4;
    list2->next->next->next = NULL;

    subtractLists(list1, list2);

    return 0;
}