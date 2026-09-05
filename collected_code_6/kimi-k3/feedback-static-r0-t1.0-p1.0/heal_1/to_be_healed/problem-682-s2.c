#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* multiply_lists(const Node *list1, const Node *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    Node *result_head = NULL;
    Node *result_tail = NULL;
    const Node *ptr1 = list1;
    
    while (ptr1 != NULL) {
        const Node *ptr2 = list2;
        while (ptr2 != NULL) {
            int product = ptr1->data * ptr2->data;
            Node *new_node = create_node(product);
            
            if (new_node == NULL) {
                free_list(result_head);
                return NULL;
            }
            
            if (result_head == NULL) {
                result_head = new_node;
                result_tail = new_node;
            } else {
                result_tail->next = new_node;
                result_tail = new_node;
            }
            
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    
    return result_head;
}

int append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) {
        return 0;
    }
    
    if (*head == NULL) {
        *head = new_node;
        return 1;
    }
    
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 1;
}

void print_list(const Node *head) {
    const Node *current = head;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *result = NULL;
    
    if (!append_node(&list1, 1) || !append_node(&list1, 2) || !append_node(&list1, 3)) {
        free_list(list1);
        return EXIT_FAILURE;
    }
    
    if (!append_node(&list2, 4) || !append_node(&list2, 5)) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }
    
    printf("List 1: ");
    print_list(list1);
    printf("List 2: ");
    print_list(list2);
    
    result = multiply_lists(list1, list2);
    
    if (result == NULL) {
        free_list(list1);
        free_list(list2);
        return EXIT_FAILURE;
    }
    
    printf("Result: ");
    print_list(result);
    
    free_list(list1);
    free_list(list2);
    free_list(result);
    
    return EXIT_SUCCESS;
}