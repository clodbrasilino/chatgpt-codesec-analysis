#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
} Node;

typedef struct ListOfLists {
    Node* head;
    struct ListOfLists* next;
} ListOfLists;

long long count_and_square(ListOfLists* head) {
    if (head == NULL) {
        return 0;
    }

    long long count = 0;
    ListOfLists* current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count * count;
}

void free_list_of_lists(ListOfLists* head) {
    ListOfLists* current = head;
    while (current != NULL) {
        ListOfLists* temp = current;
        current = current->next;
        
        Node* inner_current = temp->head;
        while (inner_current != NULL) {
            Node* inner_temp = inner_current;
            inner_current = inner_current->next;
            free(inner_temp);
        }
        
        free(temp);
    }
}

int main(void) {
    ListOfLists* list1 = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (list1 == NULL) return 1;
    list1->head = NULL;
    list1->next = NULL;

    ListOfLists* list2 = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (list2 == NULL) {
        free_list_of_lists(list1);
        return 1;
    }
    list2->head = NULL;
    list2->next = NULL;

    ListOfLists* list3 = (ListOfLists*)malloc(sizeof(ListOfLists));
    if (list3 == NULL) {
        list1->next = list2;
        free_list_of_lists(list1);
        return 1;
    }
    list3->head = NULL;
    list3->next = NULL;

    list1->next = list2;
    list2->next = list3;

    long long result = count_and_square(list1);
    printf("%lld\n", result);

    free_list_of_lists(list1);

    return 0;
}