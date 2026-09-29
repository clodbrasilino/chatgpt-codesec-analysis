#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int key;
    struct Node *next;
};

struct Node *head = NULL;
struct Node *current = NULL;

void insert(int key, int data) {
    struct Node *link = (struct Node*) malloc(sizeof(struct Node));
    if (link == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    link->key = key;
    link->data = data;
    link->next = head;
    head = link;
}

int countSublists(int data) {
    struct Node *ptr = head;
    int count = 0;
    while(ptr != NULL) {
        if(ptr->data == data) {
            count++;
        }
        ptr = ptr->next;
    }
    return count;
}

int main() {
    insert(1, 10);
    insert(2, 20);
    insert(3, 30);
    insert(4, 1);
    insert(5, 40);
    insert(6, 56); 

    printf("Number of sublists containing 1: %d\n", countSublists(1));
    printf("Number of sublists containing 10: %d\n", countSublists(10));
    printf("Number of sublists containing 30: %d\n", countSublists(30));

    return 0;
}