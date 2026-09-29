#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }
    
    struct Node* last = *head_ref;
    
    new_node->data = new_data;
    new_node->next = NULL;
    
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    
    while (last->next != NULL) {
        last = last->next;
    }
    
    last->next = new_node;
}

void free_list(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int sum_two_lists(struct Node* list1, struct Node* list2) {
    int sum = 0;
    
    while (list1 != NULL) {
        sum += list1->data;
        list1 = list1->next;
    }
    
    while (list2 != NULL) {
        sum += list2->data;
        list2 = list2->next;
    }
    
    return sum;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int total_sum = 0;
    
    append(&list1, 10);
    append(&list1, 20);
    append(&list1, 30);
    
    append(&list2, 5);
    append(&list2, 15);
    append(&list2, 25);
    
    total_sum = sum_two_lists(list1, list2);
    
    printf("Total sum: %d\n", total_sum);
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}