#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if(newNode != NULL){
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int countSublists(struct Node* start, int x)
{
    struct Node* ptr = start;
    int count = 0;

    while (ptr != NULL) {
        if (ptr->data == x)
            count++;
        ptr = ptr->next;
    }
    return count;
}

int main()
{
    struct Node* start = newNode(1);
    if(start != NULL){
        start->next = newNode(2);
        if(start->next!= NULL){
            start->next->next = newNode(1);
            if(start->next->next!=NULL){
                start->next->next->next = newNode(3);
                if(start->next->next->next!=NULL){
                    start->next->next->next->next = newNode(1);
                }
            }
        }
    }

    int x = 1;

    printf("Element %d occurs in %d sublists\n",x, countSublists(start, x));

    return 0;
}