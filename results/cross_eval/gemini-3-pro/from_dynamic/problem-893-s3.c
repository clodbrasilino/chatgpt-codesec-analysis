#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SubList {
    Node* head;
    struct SubList* next;
} SubList;

int* get_last_elements(SubList* head, int* count) {
    if (head == NULL) {
        *count = 0;
        return NULL;
    }

    int num_sublists = 0;
    SubList* current_sub = head;
    while (current_sub != NULL) {
        num_sublists++;
        current_sub = current_sub->next;
    }

    int* lasts = (int*)malloc(num_sublists * sizeof(int));
    if (lasts == NULL) {
        *count = 0;
        return NULL;
    }

    current_sub = head;
    int index = 0;
    while (current_sub != NULL) {
        Node* curr_node = current_sub->head;
        if (curr_node == NULL) {
            free(lasts);
            *count = 0;
            return NULL;
        }
        while (curr_node->next != NULL) {
            curr_node = curr_node->next;
        }
        lasts[index++] = curr_node->data;
        current_sub = current_sub->next;
    }

    *count = num_sublists;
    return lasts;
}

void free_nodes(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_sublists(SubList* head) {
    while (head != NULL) {
        SubList* temp = head;
        free_nodes(temp->head);
        head = head->next;
        free(temp);
    }
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

SubList* create_sublist() {
    SubList* new_sublist = (SubList*)malloc(sizeof(SubList));
    if (new_sublist != NULL) {
        new_sublist->head = NULL;
        new_sublist->next = NULL;
    }
    return new_sublist;
}

int main() {
    SubList* head = create_sublist();
    if (head == NULL) return 1;
    
    head->head = create_node(1);
    if (head->head == NULL) { free_sublists(head); return 1; }
    head->head->next = create_node(2);
    if (head->head->next == NULL) { free_sublists(head); return 1; }
    head->head->next->next = create_node(3);
    if (head->head->next->next == NULL) { free_sublists(head); return 1; }

    head->next = create_sublist();
    if (head->next == NULL) { free_sublists(head); return 1; }
    
    head->next->head = create_node(4);
    if (head->next->head == NULL) { free_sublists(head); return 1; }
    head->next->head->next = create_node(5);
    if (head->next->head->next == NULL) { free_sublists(head); return 1; }

    int count = 0;
    int* lasts = get_last_elements(head, &count);

    if (lasts != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d ", lasts[i]);
        }
        printf("\n");
        free(lasts);
    }

    free_sublists(head);

    return 0;
}