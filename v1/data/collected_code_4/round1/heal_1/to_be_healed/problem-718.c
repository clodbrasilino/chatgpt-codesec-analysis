#include <stdio.h>
#include <stdlib.h>

struct Node {
   int data;
   struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
   struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
   
   /* Possible weaknesses found:
    *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
    */
   new_node->data  = new_data;
   new_node->next = (*head_ref);
   (*head_ref) = new_node;
}

struct Node* alternateList(struct Node* head) {
   if (head == NULL) {
        return head;
   }
   struct Node* temp = head;
   struct Node* new_list = NULL;
   int index = 0;
   
   while(temp != NULL) {
       if(index % 2 == 0) {
           push(&new_list, temp->data);
       }
       index++;
       temp = temp->next;
   }
   return new_list;
}

void printList(struct Node* node) {
   while (node != NULL) {
      printf(" %d ", node->data);
      node = node->next;
   }
}

int main() {
   struct Node* head = NULL;
   push(&head, 6);
   push(&head, 5);
   push(&head, 4);
   push(&head, 3);
   push(&head, 2);
   push(&head, 1);
   printf("Given linked list \n");
   printList(head);
   printf("\n");
   printf("Alternate linked list \n");
   struct Node* new_list = alternateList(head);
   printList(new_list);
   printf("\n");
   
   return 0;
}