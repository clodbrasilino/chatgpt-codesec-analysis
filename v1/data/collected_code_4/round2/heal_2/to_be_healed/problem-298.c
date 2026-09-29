#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
    int data;
    struct Node *next;
};

void push(struct Node **head_ref, int new_data)
{
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

bool isPresent (struct Node *head, int data)
{
    struct Node *t = head;
    while (t != NULL)
    {
        if (t->data == data)
            return true;
        /* Possible weaknesses found:
         *  use of uninitialized value '*t.next' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        t = t->next;
    }
    return false;
}

struct Node *getIntersection(struct Node *head1, struct Node *head2)
{
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while(t1 != NULL)
    {
        if(isPresent(head2, t1->data))
            push(&result, t1->data);
        t1 = t1->next;
    }

    return result;
}

void printList (struct Node *node)
{
    while (node != NULL)
    {
        printf ("%d ", node->data);
        node = node->next;
    }
}

int main()
{
    struct Node *newNode;

    struct Node *head1 = (struct Node*) malloc(sizeof(struct Node));
    struct Node *head2 = (struct Node*) malloc(sizeof(struct Node));
    struct Node *intersection;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head1' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head1->data  = 1;
    newNode = (struct Node*) malloc (sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = 2;
    head1->next = newNode;

    newNode = (struct Node*) malloc (sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = 3;
    head1->next->next  = newNode;

    newNode = (struct Node*) malloc (sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = 4;
    head1->next ->next->next  = newNode;

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'head2' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    head2->data  = 1;
    newNode = (struct Node*) malloc (sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = 3;
    head2->next = newNode;

    newNode = (struct Node*) malloc (sizeof(struct Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->data = 5;
    head2->next->next  = newNode;

    intersection = getIntersection(head1, head2);

    printList(intersection);

    return 0;
}