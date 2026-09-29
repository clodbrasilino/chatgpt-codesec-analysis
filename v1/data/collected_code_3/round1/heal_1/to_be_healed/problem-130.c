#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int count;
};

int findMaxFrequency(int* arr, int n) {
    struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));
    for(int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'items' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        items[i].value = arr[i];
        items[i].count = 1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(items[i].value == items[j].value) {
                items[i].count++;
                arr[j] = 0;
            }
        }
    }

    int maxCount = 0;
    int maxValue;
    for(int i = 0; i < n; i++) {
        if(items[i].count > maxCount) {
            maxCount = items[i].count;
            maxValue = items[i].value;
        }
    }

    free(items);
    /* Possible weaknesses found:
     *  use of uninitialized value 'maxValue' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    return maxValue;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxFrequencyItem = findMaxFrequency(arr, n);
    printf("Item with maximum frequency: %d\n", maxFrequencyItem);
    return 0;
}