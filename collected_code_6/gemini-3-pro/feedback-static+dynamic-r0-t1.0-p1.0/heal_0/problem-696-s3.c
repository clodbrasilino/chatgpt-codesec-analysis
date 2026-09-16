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

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

List* create_list(Node* head) {
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        exit(EXIT_FAILURE);
    }
    new_list->head = head;
    new_list->next = NULL;
    return new_list;
}

void append_node(Node** head, int data) {
    if (head == NULL) {
        return;
    }
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
    }
}

void append_list(List** head, Node* node_head) {
    if (head == NULL) {
        return;
    }
    List* new_list = create_list(node_head);
    if (*head == NULL) {
        *head = new_list;
    } else {
        List* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_list;
    }
}

Node* clone_nodes(Node* head) {
    Node* new_head = NULL;
    Node* curr = head;
    while (curr != NULL) {
        append_node(&new_head, curr->data);
        curr = curr->next;
    }
    return new_head;
}

Node* concatenate_nodes(Node* list1, Node* list2) {
    Node* new_head = clone_nodes(list1);
    Node* cloned_list2 = clone_nodes(list2);

    if (new_head == NULL) {
        return cloned_list2;
    }

    Node* curr = new_head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = cloned_list2;
    return new_head;
}

List* zip_lists(List* l1, List* l2) {
    List* zipped = NULL;
    List* curr1 = l1;
    List* curr2 = l2;

    while (curr1 != NULL && curr2 != NULL) {
        Node* concatenated = concatenate_nodes(curr1->head, curr2->head);
        append_list(&zipped, concatenated);
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return zipped;
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

void print_nodes(Node* head) {
    Node* curr = head;
    printf("[");
    while (curr != NULL) {
        printf("%d", curr->data);
        if (curr->next != NULL) {
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]");
}

void print_lists(List* head) {
    List* curr = head;
    printf("[");
    while (curr != NULL) {
        print_nodes(curr->head);
        if (curr->next != NULL) {
            printf(", ");
        }
        curr = curr->next;
    }
    printf("]\n");
}

int main(void) {
    Node* n1 = NULL;
    append_node(&n1, 1);
    append_node(&n1, 2);

    Node* n2 = NULL;
    append_node(&n2, 3);
    
    List* l1 = NULL;
    append_list(&l1, n1);
    append_list(&l1, n2);

    Node* n3 = NULL;
    append_node(&n3, 4);

    Node* n4 = NULL;
    append_node(&n4, 5);
    append_node(&n4, 6);

    List* l2 = NULL;
    append_list(&l2, n3);
    append_list(&l2, n4);

    List* zipped = zip_lists(l1, l2);

    print_lists(zipped);

    free_lists(l1);
    free_lists(l2);
    free_lists(zipped);

    return 0;
}