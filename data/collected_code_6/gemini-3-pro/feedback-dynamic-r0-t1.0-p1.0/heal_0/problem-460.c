#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

int* get_first_elements(List* list_of_lists, int* return_size) {
    if (list_of_lists == NULL || return_size == NULL) {
        if (return_size != NULL) {
            *return_size = 0;
        }
        return NULL;
    }

    int count = 0;
    List* currList = list_of_lists;
    while (currList != NULL) {
        if (currList->head != NULL) {
            count++;
        }
        currList = currList->next;
    }

    *return_size = count;
    if (count == 0) {
        return NULL;
    }

    int* result = (int*)malloc(count * sizeof(int));
    if (result == NULL) {
        *return_size = 0;
        return NULL;
    }

    int index = 0;
    currList = list_of_lists;
    while (currList != NULL) {
        if (currList->head != NULL) {
            result[index++] = currList->head->data;
        }
        currList = currList->next;
    }

    return result;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

List* create_list(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list != NULL) {
        new_list->head = head;
        new_list->next = NULL;
    }
    return new_list;
}

void free_nodes(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_lists(List* head) {
    while (head != NULL) {
        List* temp = head;
        head = head->next;
        free_nodes(temp->head);
        free(temp);
    }
}

int main(void) {
    Node* n1 = create_node(1);
    if (n1 == NULL) return 1;
    Node* n2 = create_node(2);
    if (n2 == NULL) { free_nodes(n1); return 1; }
    n1->next = n2;

    Node* n3 = create_node(3);
    if (n3 == NULL) { free_nodes(n1); return 1; }
    Node* n4 = create_node(4);
    if (n4 == NULL) { free_nodes(n1); free_nodes(n3); return 1; }
    n3->next = n4;

    List* l1 = create_list(n1);
    if (l1 == NULL) { free_nodes(n1); free_nodes(n3); return 1; }
    List* l2 = create_list(n3);
    if (l2 == NULL) { free_lists(l1); free_nodes(n3); return 1; }
    
    l1->next = l2;

    int return_size = 0;
    int* first_elements = get_first_elements(l1, &return_size);

    if (first_elements != NULL) {
        for (int i = 0; i < return_size; i++) {
            printf("%d ", first_elements[i]);
        }
        printf("\n");
        free(first_elements);
    }

    free_lists(l1);

    return 0;
}