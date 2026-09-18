#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TupleFrequency {
    char *tuple;
    int freq;
    struct TupleFrequency *next;
} TupleFrequency;

TupleFrequency *createTuple(char *tuple){
    TupleFrequency *newTuple = (TupleFrequency*)malloc(sizeof(TupleFrequency));
    if (newTuple == NULL){
        printf("Memory allocation failed.\n");
        exit(0);
    }
    newTuple->tuple = NULL;
    if (tuple != NULL) {
        newTuple->tuple = strdup(tuple);
        if (newTuple->tuple == NULL) {
            printf("Memory allocation for tuple field failed.\n");
            free(newTuple);
            exit(0);
        }
    }
    newTuple->freq = 1;
    newTuple->next = NULL;
    return newTuple;
}

void insertOrUpdateTuple(TupleFrequency **head, char *tuple){
    if (*head == NULL) {
        *head = createTuple(tuple);
        return;
    }
    TupleFrequency *current = *head;
    while(current){
        if(current->tuple && strcmp(current->tuple, tuple) == 0){
            current->freq++;
            return;
        }
        if(current->next == NULL) {
            current->next = createTuple(tuple);
            return;
        }
        current = current->next;
    }
}

void printTupleFrequencies(TupleFrequency *head){
    printf("TUPLE FREQUENCIES:\n");
    while(head){
        printf("%s: %d\n", head->tuple, head->freq);
        head = head->next;
    }
}

int main() {
    TupleFrequency *head = NULL; 
    char *data[] = {"abc", "def", "abc", "xyz", "abc", "def"};
    int len = sizeof(data)/sizeof(data[0]);
    for (int i = 0; i < len; i++)
        insertOrUpdateTuple(&head, data[i]);
    printTupleFrequencies(head);
    return 0;
}