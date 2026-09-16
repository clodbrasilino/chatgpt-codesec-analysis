#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Tuple;

void swap(Tuple* a, Tuple* b) {
    Tuple temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Tuple arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].value > arr[largest].value)
        largest = left;

    if (right < n && arr[right].value > arr[largest].value)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildMaxHeap(Tuple arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

Tuple* findMinKRecords(Tuple* tuples, int num_tuples, int k) {
    if (!tuples || num_tuples <= 0 || k <= 0) {
        return NULL;
    }

    if (k > num_tuples) {
        k = num_tuples;
    }

    Tuple* result = (Tuple*)malloc(k * sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        result[i] = tuples[i];
    }

    buildMaxHeap(result, k);

    for (int i = k; i < num_tuples; i++) {
        if (tuples[i].value < result[0].value) {
            result[0] = tuples[i];
            maxHeapify(result, k, 0);
        }
    }

    return result;
}

int main(void) {
    int num_tuples = 7;
    int k = 3;
    Tuple tuples[] = {
        {1, 50}, {2, 10}, {3, 30}, {4, 20}, {5, 60}, {6, 5}, {7, 40}
    };

    Tuple* min_k = findMinKRecords(tuples, num_tuples, k);
    if (!min_k) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < k; i++) {
        printf("ID: %d, Value: %d\n", min_k[i].id, min_k[i].value);
    }

    free(min_k);
    return EXIT_SUCCESS;
}