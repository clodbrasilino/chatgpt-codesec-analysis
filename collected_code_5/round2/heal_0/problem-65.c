#include <stdio.h>

struct Node {
    int data;
    int *next;
};

int sum(struct Node* head)
{
    if (head == NULL)
        return 0;
    return head->data + sum(head->next);
}

int main(){
    struct Node node3 = {3, NULL};
    struct Node node2 = {2, &node3};
    struct Node	node1 = {1, &node2};

    struct Node* head = &node1;

    printf("%d\n", sum(head));
    return 0;
}