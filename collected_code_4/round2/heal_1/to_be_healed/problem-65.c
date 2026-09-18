#include <stdio.h>

struct Node {
    int data;
    int *next;
};

/* Possible weaknesses found:
 *  expected 'struct Node *' but argument is of type 'int *'
 */
int sum(struct Node* head)
{
    if (head == NULL)
        return 0;
    /* Possible weaknesses found:
     *  passing argument 1 of 'sum' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    return head->data + sum(head->next);
}

int main(){
    struct Node node3 = {3, NULL};
    /* Possible weaknesses found:
     *  initialization of 'int *' from incompatible pointer type 'struct Node *' [-Wincompatible-pointer-types]
     *  (near initialization for 'node2.next')
     */
    struct Node node2 = {2, &node3};
    /* Possible weaknesses found:
     *  initialization of 'int *' from incompatible pointer type 'struct Node *' [-Wincompatible-pointer-types]
     *  (near initialization for 'node1.next')
     */
    struct Node	node1 = {1, &node2};

    struct Node* head = &node1;

    printf("%d\n", sum(head));
    return 0;
}