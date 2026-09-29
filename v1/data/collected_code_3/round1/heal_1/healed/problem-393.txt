#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int findLength(struct Node* head) {
    int count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

struct Node* findLongestList(struct Node* list1, struct Node* list2) {
    int len1 = findLength(list1);
    int len2 = findLength(list2);
    if (len1 > len2) {
        return list1;
    } else {
        return list2;
    }
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    if(node == NULL){
        return NULL;
    } 
    node->data = data;
    node->next = NULL;
    return node;
}

int main() {
    struct Node* list1 = newNode(1);
    if(list1 == NULL){
        return 1;
    } 
    list1->next = newNode(2);
    if(list1->next == NULL){
        free(list1);
        return 1;
    } 
    list1->next->next = newNode(3);
    if(list1->next->next == NULL){
        free(list1->next);
        free(list1);
        return 1;
    } 

    struct Node* list2 = newNode(1);
    if(list2 == NULL){
        free(list1->next->next);
        free(list1->next);
        free(list1);
        return 1;
    } 
    list2->next = newNode(2);
    if(list2->next == NULL){
        free(list2);
        free(list1->next->next);
        free(list1->next);
        free(list1);
        return 1;
    } 

    struct Node* longestList = findLongestList(list1, list2);

    printf("The longest list is: ");
    while (longestList != NULL) {
        printf("%d ", longestList->data);
        longestList = longestList->next;
    }

    return 0;
}