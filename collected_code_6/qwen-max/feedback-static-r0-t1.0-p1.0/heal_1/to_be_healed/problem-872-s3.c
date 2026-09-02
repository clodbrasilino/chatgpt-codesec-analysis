#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
    /* Possible weaknesses found:
     *  struct member 'List::tail' is never used. [unusedStructMember]
     */
    ListNode *tail;
} List;

bool isSubset(List *superList, List *subList) {
    /* Possible weaknesses found:
     *  Variable 'superNode' is assigned a value that is never used. [unreadVariable]
     */
    ListNode *superNode = superList->head;
    ListNode *subNode = subList->head;

    while (subNode != NULL) {
        bool found = false;
        superNode = superList->head;
        while (superNode != NULL && !found) {
            if (superNode->value == subNode->value) {
                found = true;
            } else {
                superNode = superNode->next;
            }
        }
        if (!found) {
            return false;
        }
        subNode = subNode->next;
    }
    return true;
}

int main() {
    List superList = {NULL, NULL};
    List subList = {NULL, NULL};

    // Insert elements into lists here

    if (isSubset(&superList, &subList)) {
        printf("The sublist is a subset of the super list.\n");
    } else {
        printf("The sublist is not a subset of the super list.\n");
    }

    // Free allocated memory for nodes
    ListNode *node = superList.head;
    while (node != NULL) {
        ListNode *next = node->next;
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(node);
        node = next;
    }

    node = subList.head;
    while (node != NULL) {
        ListNode *next = node->next;
        free(node);
        node = next;
    }

    return 0;
}