#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

// The structure for Node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data)
{
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'malloc' [-Wbuiltin-declaration-mismatch]
     *  include '<stdlib.h>' or provide a declaration of 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to count the number of sublists containing a 
// specific element
int countSublists(struct Node* start, int x)
{
    struct Node* ptr = start;
    int count = 0;

    // Traverse the list
    while (ptr != NULL) {
        if (ptr->data == x)
            count++;
        ptr = ptr->next;
    }
    return count;
}

// Main function
int main()
{
    struct Node* start = newNode(1);
    start->next = newNode(2);
    start->next->next = newNode(1);
    start->next->next->next = newNode(3);
    start->next->next->next->next = newNode(1);

    int x = 1;

    printf("Element %d occurs in %d sublists\n",x, countSublists(start, x));

    return 0;
}