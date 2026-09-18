#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
}node;

typedef struct list
{
    node *head;
    struct list *next;
}list;

node* create_node(int val)
{
    node* newNode = malloc(sizeof(node));
    if(!newNode) 
    {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

list* create_list(node* nodeHead)
{
    list* newList = malloc(sizeof(list));
    if(!newList) 
    {
        printf("Memory error\n");
        exit(EXIT_FAILURE);
    }
    newList->head = nodeHead;
    newList->next = NULL;
    return newList;
}

void remove_sublists(list** root, int start, int end)
{
    list* previous = NULL;
    list* current = *root;
    while(current != NULL)
    {
        node* nodeCurrent = current->head;
        while(nodeCurrent != NULL)
        {
            if(nodeCurrent->val < start || nodeCurrent->val > end)
            {
                if( previous != NULL )
                {
                    previous->next = current->next;
                }
                else
                {
                    *root = current->next;
                }
                free(current);
                break;
            }
            nodeCurrent = nodeCurrent->next;
        }
        previous = current;
        /* Possible weaknesses found:
         *  use after 'free' of 'current' [CWE-416] [-Wanalyzer-use-after-free]
         */
        current = current->next;
    }
}

int main()
{
    node* node1 = create_node(1);
    node* node2 = create_node(2);
    node1->next = node2;
    node* node3 = create_node(5);
    node* node4 = create_node(6);
    node3->next = node4;

    list* list1 = create_list(node1);
    list* list2 = create_list(node3);
    list1->next = list2;

    remove_sublists(&list1, 1, 4);
    return 0;
}