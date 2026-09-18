#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* getNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    
    if(newNode==NULL){
        printf("Failed to allocate memory\n");
        exit(0);
    }
    
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int data)
{
    if (head == NULL)
        head = getNode(data);
    else
    {
        struct Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = getNode(data);
    }
    return head;
}

int getNth(struct Node* head, int n)
{
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL)
    {
        if (++count == n)
            return(temp->data);
        temp = temp->next;
    }
    
    printf("The list contains less than n nodes\n");
    return -1;
}

int main(void)
{
    struct Node* head = NULL;
    int x = 10, n=4;
    
    for (int i=1; i<=x; i++)
        head = insertEnd(head, i);
        
    printf("Element at position %d is %d\n", n, getNth(head, n));
    return 0;
}
