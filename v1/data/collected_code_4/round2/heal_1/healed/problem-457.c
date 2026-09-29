#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* new_node(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if(node != NULL){
        node->data = data;
        node->next = NULL;
    }
    return node;
}

int get_length(struct Node* head) {
    int len = 0;
    while(head) {
        len++;
        head = head->next;
    }
    return len;
}

struct Node* get_min_length_sublist(struct Node* head) {
    struct Node *min_head = NULL, *current_head = head;
    int min_len = get_length(head);
    while(current_head) {
        struct Node* current = current_head;
        int current_len = get_length(current);
        if(current_len < min_len) {
            min_len = current_len;
            min_head = current;
        }
        current_head = current_head->next;
    }
    return min_head;
}

int main() {
    struct Node* head = new_node(1);
    if(head != NULL){
       head->next = new_node(2);
       if(head->next != NULL){
          head->next->next = new_node(3);
          if(head->next->next != NULL){
             head->next->next->next = new_node(4);

             struct Node* sublist = get_min_length_sublist(head);
             while(sublist) {
                printf("%d ", sublist->data);
                sublist = sublist->next;
             }
             printf("\n");
          }
       }
    }
    return 0;
}