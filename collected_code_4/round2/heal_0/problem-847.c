#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node* create_node(int data) {
    node* new_node = (node *) malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    return new_node;
}

node* copy_list(node* head) {
    if (head == NULL) return NULL;
    
    node* new_list = create_node(head->data);
    node* tmp = new_list;
    node* cur_node = head->next;
    
    while(cur_node != NULL) {
        tmp->next = create_node(cur_node->data);
        tmp = tmp->next;
        cur_node = cur_node->next;
    }

    return new_list;
}
  
void print_list(node* head)
{
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }

    printf("\n");
}

node* free_list(node* head) {
    while(head != NULL) {
        node* tmp = head;
        head = head->next;
        free(tmp);
    }
    
    return NULL;
}

int main() {
    node* head = create_node(5);
    head->next = create_node(15);
    head->next->next = create_node(25);
    
    printf("Original List: ");
    print_list(head);
  
    node* copied_list = copy_list(head);
    
    printf("Copied List: ");
    print_list(copied_list);
    
    head = free_list(head);
    copied_list = free_list(copied_list);
    
    return 0;
}