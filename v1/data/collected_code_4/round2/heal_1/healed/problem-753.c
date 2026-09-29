#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int key;
    int value;
} Tuple;

void swap(Tuple* a, Tuple* b) {
    Tuple t = *a;
    *a = *b;
    *b = t;
}

int partition(Tuple arr[], int low, int high) {
    int pivot = arr[high].value;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].value < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Tuple arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

Tuple* findMinKRecords(Tuple* tuples, int tupleSize, int k) {
    if (k > tupleSize) {
        return NULL;
    }

    quickSort(tuples, 0, tupleSize - 1);

    Tuple* minKTuples = (Tuple*)malloc(k * sizeof(Tuple));
    for(int i = 0; i < k; i++) {
        minKTuples[i] = tuples[i];
    }

    return minKTuples;
}

int main() {
    int tupleSize = 5;
    Tuple tuples[5] = {{1, 100}, {2, 20}, {3, 300}, {4, 40}, {5, 500}};

    int k = 2;
    Tuple* minKTuples = findMinKRecords(tuples, tupleSize, k);

    if(minKTuples == NULL) {
        printf("k is larger than tuple size.\n");
    } else {
        for(int i = 0; i < k; i++) {
            printf("Key: %d Value: %d\n", minKTuples[i].key, minKTuples[i].value);
        }
        free(minKTuples);
    }

    return 0;
}