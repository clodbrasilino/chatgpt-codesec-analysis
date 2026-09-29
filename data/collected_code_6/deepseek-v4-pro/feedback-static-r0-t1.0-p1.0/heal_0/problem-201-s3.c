#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int are_all_elements_same(struct Node *head) {
    if (head == NULL) {
        return 1;
    }
    
    int first_value = head->data;
    struct Node *current = head->next;
    
    while (current != NULL) {
        if (current->data != first_value) {
            return 0;
        }
        current = current->next;
    }
    
    return 1;
}

struct Node *create_node(int value) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head, int value) {
    struct Node *new_node = create_node(value);
    if (new_node == NULL) {
        return;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    struct Node *list3 = NULL;
    
    append_node(&list1, 5);
    append_node(&list1, 5);
    append_node(&list1, 5);
    
    append_node(&list2, 3);
    append_node(&list2, 3);
    append_node(&list2, 7);
    
    if (are_all_elements_same(list1)) {
        printf("List 1: All elements are same\n");
    } else {
        printf("List 1: Elements are not same\n");
    }
    
    if (are_all_elements_same(list2)) {
        printf("List 2: All elements are same\n");
    } else {
        printf("List 2: Elements are not same\n");
    }
    
    if (are_all_elements_same(list3)) {
        printf("List 3: All elements are same\n");
    } else {
        printf("List 3: Elements are not same\n");
    }
    
    free_list(list1);
    free_list(list2);
    free_list(list3);
    
    return 0;
}