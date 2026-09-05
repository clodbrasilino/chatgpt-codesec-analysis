#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(struct Node **head_ref, int data) {
    struct Node *new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    struct Node *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_node;
}

struct Node *multiply_lists(struct Node *list1, struct Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    struct Node *result = NULL;
    struct Node *l1_curr = list1;
    while (l1_curr != NULL) {
        struct Node *l2_curr = list2;
        while (l2_curr != NULL) {
            int product = l1_curr->data * l2_curr->data;
            append_node(&result, product);
            l2_curr = l2_curr->next;
        }
        l1_curr = l1_curr->next;
    }
    return result;
}

void free_list(struct Node *head) {
    struct Node *tmp = NULL;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(struct Node *head) {
    struct Node *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

int main(void) {
    struct Node *list1 = NULL;
    struct Node *list2 = NULL;
    
    append_node(&list1, 1);
    append_node(&list1, 2);
    append_node(&list1, 3);
    
    append_node(&list2, 4);
    append_node(&list2, 5);
    
    struct Node *result = multiply_lists(list1, list2);
    
    print_list(result);
    
    free_list(list1);
    free_list(list2);
    free_list(result);
    
    list1 = NULL;
    list2 = NULL;
    result = NULL;
    
    return 0;
}