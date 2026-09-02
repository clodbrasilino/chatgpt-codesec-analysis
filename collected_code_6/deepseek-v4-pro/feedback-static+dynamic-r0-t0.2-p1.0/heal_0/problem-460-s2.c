#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

int* get_first_elements(Sublist* sublists, int* count) {
    if (sublists == NULL || count == NULL) {
        return NULL;
    }

    int size = 0;
    Sublist* current = sublists;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    int* result = (int*)malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    current = sublists;
    int index = 0;
    while (current != NULL) {
        if (current->head != NULL) {
            result[index] = current->head->data;
        } else {
            free(result);
            return NULL;
        }
        index++;
        current = current->next;
    }

    *count = size;
    return result;
}

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Sublist* create_sublist(Node* head) {
    Sublist* sublist = (Sublist*)malloc(sizeof(Sublist));
    if (sublist == NULL) {
        return NULL;
    }
    sublist->head = head;
    sublist->next = NULL;
    return sublist;
}

void free_sublists(Sublist* sublists) {
    Sublist* current = sublists;
    while (current != NULL) {
        Sublist* next_sublist = current->next;
        Node* node = current->head;
        while (node != NULL) {
            Node* next_node = node->next;
            free(node);
            node = next_node;
        }
        free(current);
        current = next_sublist;
    }
}

int main() {
    Node* n1 = create_node(10);
    Node* n2 = create_node(20);
    Node* n3 = create_node(30);
    n1->next = n2;
    n2->next = n3;

    Node* n4 = create_node(40);
    Node* n5 = create_node(50);
    n4->next = n5;

    Node* n6 = create_node(60);

    Sublist* s1 = create_sublist(n1);
    Sublist* s2 = create_sublist(n4);
    Sublist* s3 = create_sublist(n6);

    s1->next = s2;
    s2->next = s3;

    int count = 0;
    int* first_elements = get_first_elements(s1, &count);

    if (first_elements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d ", first_elements[i]);
        }
        printf("\n");
        free(first_elements);
    }

    free_sublists(s1);

    return 0;
}