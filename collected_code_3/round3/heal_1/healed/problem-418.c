#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if(new_node != NULL){
        new_node->data = new_data;
        new_node->next = (*head_ref);
        (*head_ref) = new_node;
    }
}

int maxSubList(struct Node* head) {
    if(head == NULL){
        return 0;
    }
    int max_count = 0, count = 0;
    int prev_data = head->data;
    while (head != NULL) {
        if (head->data == prev_data) {
            count++;
        } else {
            if (count > max_count) {
                max_count = count;
            }
            count = 1;
        }
        prev_data = head->data;
        head = head->next;
    }
    if (count > max_count) {
        max_count = count;
    }
    return max_count;
}

int main() {
    struct Node* head = NULL;
    push(&head, 1);
    push(&head, 1);
    push(&head, 1);
    push(&head, 2);
    push(&head, 2);
    push(&head, 3);
    push(&head, 3);
    push(&head, 3);
    push(&head, 3);
    printf("Length of maximum sublist is %d\n", maxSubList(head));
    return 0;
}