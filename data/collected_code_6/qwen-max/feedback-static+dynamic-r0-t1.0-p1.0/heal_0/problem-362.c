#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int element;
    int count;
} ElementCount;

int compare(const void *a, const void *b) {
    return ((ElementCount *)b)->count - ((ElementCount *)a)->count;
}

ElementCount* findMaxOccurrences(int *arr, int size) {
    if (size <= 0) return NULL;

    ElementCount *elements = (ElementCount *)malloc(size * sizeof(ElementCount));
    if (elements == NULL) return NULL;

    for (int i = 0; i < size; i++) {
        elements[i].element = arr[i];
        elements[i].count = 1;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] == arr[i]) {
                elements[i].count++;
                arr[j] = INT_MIN; // Mark as counted
            }
        }
    }

    qsort(elements, size, sizeof(ElementCount), compare);

    for (int i = 0; i < size; i++) {
        if (elements[i].element != INT_MIN) {
            return &elements[i];
        }
    }

    free(elements);
    return NULL;
}

int main() {
    int arr[] = {3, 1, 2, 3, 3, 4, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    ElementCount *maxOccurrence = findMaxOccurrences(arr, size);

    if (maxOccurrence != NULL) {
        printf("Element with maximum occurrences: %d, Count: %d\n", maxOccurrence->element, maxOccurrence->count);
    } else {
        printf("No valid element found.\n");
    }

    return 0;
}