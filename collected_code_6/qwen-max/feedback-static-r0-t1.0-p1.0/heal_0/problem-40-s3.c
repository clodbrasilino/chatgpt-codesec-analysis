#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frequency;
} ElementFreq;

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

void insert(List *lst, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) exit(EXIT_FAILURE);
    newNode->value = value;
    newNode->next = lst->head;
    lst->head = newNode;
}

int getFrequency(List *list, int value) {
    int freq = 0;
    Node *current = list->head;
    while (current != NULL) {
        if (current->value == value) {
            freq++;
        }
        current = current->next;
    }
    return freq;
}

void calculateFrequencies(List *lists, int numLists, ElementFreq *freqs, int size) {
    for (int i = 0; i < size; i++) {
        freqs[i].value = i;
        freqs[i].frequency = 0;
    }

    for (int i = 0; i < numLists; i++) {
        Node *current = lists[i].head;
        while (current != NULL) {
            freqs[current->value].frequency += 1;
            current = current->next;
        }
    }
}

int main() {
    int numLists = 3;
    List lists[3] = {{NULL}, {NULL}, {NULL}};
    
    insert(&lists[0], 0);
    insert(&lists[0], 1);
    insert(&lists[0], 2);

    insert(&lists[1], 2);
    insert(&lists[1], 3);
    
    insert(&lists[2], 1);
    insert(&lists[2], 4);

    int maxSize = 5;
    ElementFreq freqs[5];

    calculateFrequencies(lists, numLists, freqs, maxSize);

    for (int i = 0; i < maxSize; i++) {
        printf("%d: %d\n", freqs[i].value, freqs[i].frequency);
    }

    for (int i = 0; i < numLists; i++) {
        Node *current = lists[i].head;
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}