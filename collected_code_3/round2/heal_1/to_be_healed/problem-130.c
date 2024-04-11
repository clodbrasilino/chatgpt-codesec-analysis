#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int count;
};

int findMaxFrequency(int* arr, int n) {
    struct Item* freq = (struct Item*)malloc(sizeof(struct Item) * n);
    int i, j, maxCountIndex = 0;
    for(i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'freq' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        freq[i].value = arr[i];
        freq[i].count = 1;
    }
    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                freq[i].count++;
                arr[j] = -1;
            }
        }
        if(freq[i].count > freq[maxCountIndex].count) {
            maxCountIndex = i;
        }
    }
    int maxFrequencyItem = freq[maxCountIndex].value;
    free(freq);
    return maxFrequencyItem;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxFrequencyItem = findMaxFrequency(arr, n);
    printf("Item with maximum frequency: %d\n", maxFrequencyItem);
    return 0;
}