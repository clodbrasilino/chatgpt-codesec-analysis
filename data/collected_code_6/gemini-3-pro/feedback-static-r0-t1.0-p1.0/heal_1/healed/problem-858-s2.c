#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* list;
    struct ListOfLists* next;
} ListOfLists;

long long int count_and_square_lists(const ListOfLists* head) {
    long long int count = 0;
    const ListOfLists* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count * count;
}

int main(void) {
    ListOfLists* head = NULL;
    ListOfLists* temp = NULL;
    
    head = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (head == NULL) {
        return 1;
    }
    head->list = (Node*)malloc(sizeof(Node));
    if (head->list != NULL) {
        head->list->next = NULL;
    }
    head->next = NULL;
    
    head->next = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (head->next == NULL) {
        if (head->list != NULL) {
            free(head->list);
        }
        free(head);
        return 1;
    }
    head->next->list = (Node*)malloc(sizeof(Node));
    if (head->next->list != NULL) {
        head->next->list->next = NULL;
    }
    head->next->next = NULL;
    
    head->next->next = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (head->next->next == NULL) {
        if (head->next->list != NULL) {
            free(head->next->list);
        }
        free(head->next);
        if (head->list != NULL) {
            free(head->list);
        }
        free(head);
        return 1;
    }
    head->next->next->list = (Node*)malloc(sizeof(Node));
    if (head->next->next->list != NULL) {
        head->next->next->list->next = NULL;
    }
    head->next->next->next = NULL;
    
    long long int result = count_and_square_lists(head);
    
    printf("%lld\n", result);
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        if (temp->list != NULL) {
            free(temp->list);
        }
        free(temp);
    }
    
    return 0;
}