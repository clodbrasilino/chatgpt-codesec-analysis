#include <stdio.h>
#include <stdlib.h>

typedef struct NestedList {
    int *array;
    int size;
    struct NestedList *next;
} NestedList;

NestedList *createNestedList(int *array, int size);
NestedList *appendNestedList(NestedList *head, int *array, int size);

int *flatten(NestedList *head, int *size);

int main() {

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {6, 7, 8, 9};
    int size, *flattenArray, i;
    
    NestedList *nestedList = createNestedList(arr1, sizeof(arr1)/sizeof(int));
    appendNestedList(nestedList, arr2, sizeof(arr2)/sizeof(int));
    appendNestedList(nestedList, arr3, sizeof(arr3)/sizeof(int));

    flattenArray = flatten(nestedList, &size);

    for(i = 0; i < size; i++) {
        printf("%d ", flattenArray[i]);
    }
    
    free(flattenArray);

    return 0;
}

NestedList *createNestedList(int *array, int size) {
    NestedList *newNode = (NestedList*) malloc(sizeof(NestedList));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->array = array;
    newNode->size = size;
    newNode->next = NULL;
    
    return newNode;
}

NestedList *appendNestedList(NestedList *head, int *array, int size) {
     
    NestedList *newNode = createNestedList(array, size);
    NestedList *current = head;

    while(current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;

    return head;
}

int *flatten(NestedList *head, int *size) {

    int i = 0, j, totalSize = 0;
    NestedList *current = head;

    while(current != NULL) {
        totalSize += current->size;
        current = current->next;
    }

    int *flattenArray = (int*) malloc(totalSize * sizeof(int));
    current = head;

    while(current != NULL) {
        for(j = 0; j < current->size; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'flattenArray' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            flattenArray[i++] = current->array[j];
        }
        current = current->next;
    }

    *size = totalSize;
    return flattenArray;
}