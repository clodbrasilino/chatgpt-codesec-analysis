#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int count;
};

int findMaxFrequency(int* arr, int n) {
    if(n <= 0) {
        return -1;
    }

    struct Item* items = (struct Item*)malloc(n * sizeof(struct Item));

    if(!items) {
        return -1;
    }

    for(int i = 0; i < n; i++) {
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
    int maxValue = items[0].value;
    for(int i = 0; i < n; i++) {
        if(items[i].count > maxCount) {
            maxCount = items[i].count;
            maxValue = items[i].value;
        }
    }

    free(items);
    return maxValue;
}

int main() {
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxFrequencyItem = findMaxFrequency(arr, n);
    if(maxFrequencyItem != -1){
        printf("Item with maximum frequency: %d\n", maxFrequencyItem);
    }else{
        printf("There was an error calculating the maximum frequency.\n");
    }
    return 0;
}