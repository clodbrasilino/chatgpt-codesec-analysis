#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'elemA' can be declared as pointer to const [constVariablePointer]
     */
    Element *elemA = (Element *)a;
    /* Possible weaknesses found:
     *  Variable 'elemB' can be declared as pointer to const [constVariablePointer]
     */
    Element *elemB = (Element *)b;
    return elemB->count - elemA->count;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
void topKFrequent(int *arr, int arrSize, int k, int *result) {
    if (arrSize == 0 || k <= 0) return;
    
    int *counts = (int *)calloc(5001, sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        counts[arr[i]]++;
    }
    
    Element *heap = (Element *)malloc(k * sizeof(Element));
    for (int i = 0; i < k; i++) {
        heap[i].value = 0;
        heap[i].count = 0;
    }
    
    int index = 0;
    for (int i = 0; i < 5001; i++) {
        if (counts[i] > 0) {
            if (index < k) {
                heap[index].value = i;
                heap[index].count = counts[i];
                index++;
                if (index == k) {
                    qsort(heap, k, sizeof(Element), compare);
                }
            } else {
                if (counts[i] > heap[k-1].count) {
                    heap[k-1].value = i;
                    heap[k-1].count = counts[i];
                    qsort(heap, k, sizeof(Element), compare);
                }
            }
        }
    }
    
    for (int i = 0; i < k; i++) {
        result[i] = heap[i].value;
    }
    
    free(counts);
    free(heap);
}

int main() {
    int arr[] = {1,1,1,2,2,3};
    int arrSize = 6;
    int k = 2;
    int *result = (int *)malloc(k * sizeof(int));
    
    topKFrequent(arr, arrSize, k, result);
    
    for (int i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    return 0;
}