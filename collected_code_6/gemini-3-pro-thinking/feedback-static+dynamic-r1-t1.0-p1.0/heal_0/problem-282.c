#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERR_MEMORY -1
#define ERR_PARAM -2

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void free_list(Node** head);
int append_node(Node** head, int data);
bool contains(const Node* head, int data);
int subtract_lists(const Node* list1, const Node* list2, Node** result);
void print_list(const Node* head);

void free_list(Node** head) {
    if (!head) {
        return;
    }
    
    Node* current = *head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

int append_node(Node** head, int data) {
    if (!head) {
        return ERR_PARAM;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        return ERR_MEMORY;
    }
    
    new_node->data = data;
    new_node->next = NULL;

    if (!*head) {
        *head = new_node;
        return SUCCESS;
    }

    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    
    return SUCCESS;
}

bool contains(const Node* head, int data) {
    const Node* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

int subtract_lists(const Node* list1, const Node* list2, Node** result) {
    if (!result) {
        return ERR_PARAM;
    }
    
    *result = NULL;
    const Node* current = list1;

    while (current) {
        if (!contains(list2, current->data)) {
            int status = append_node(result, current->data);
            if (status != SUCCESS) {
                free_list(result);
                return status;
            }
        }
        current = current->next;
    }
    
    return SUCCESS;
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;
    int status;
    size_t i;

    int data1[] = {1, 2, 3, 4, 5, 6, 7};
    int data2[] = {2, 4, 6};
    
    size_t len1 = sizeof(data1) / sizeof(data1[0]);
    size_t len2 = sizeof(data2) / sizeof(data2[0]);

    for (i = 0; i < len1; ++i) {
        if (append_node(&list1, data1[i]) != SUCCESS) {
            free_list(&list1);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < len2; ++i) {
        if (append_node(&list2, data2[i]) != SUCCESS) {
            free_list(&list1);
            free_list(&list2);
            return EXIT_FAILURE;
        }
    }

    status = subtract_lists(list1, list2, &result);
    
    if (status == SUCCESS) {
        print_list(result);
    }

    free_list(&list1);
    free_list(&list2);
    free_list(&result);

    return (status == SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}