#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int sum_lists(struct Node *list1, struct Node *list2) {
    int sum = 0;
    struct Node *current1 = list1;
    struct Node *current2 = list2;
    
    while (current1 != NULL) {
        sum += current1->data;
        current1 = current1->next;
    }
    
    while (current2 != NULL) {
        sum += current2->data;
        current2 = current2->next;
    }
    
    return sum;
}

struct Node *create_node(int value) {
    struct Node *new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node **head, int value) {
    struct Node *new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    int result;
    
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    
    append_node(&list2, 4);
    append_node(&list2, 5);
    append_node(&list2, 6);
    
    result = sum_lists(list1, list2);
    printf("Sum: %d\n", result);
    
    free_list(list1);
    free_list(list2);
    
    return 0;
}