#include<stdio.h>

struct counter {
    int key;
    int value;
};

void sortCounterByValue(struct counter *arr, int n) {
    for(int i=1; i<n; i++) {
        struct counter temp = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j].value < temp.value) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

int main() {
    struct counter counters[5] = {
    {1, 5},
    {2, 2},
    {3, 7},
    {4, 1},
    {5, 4}
    };

    sortCounterByValue(counters, 5);

    for(int i=0; i<5; i++) {
        printf("Counter %d: key=%d, value=%d\n", i+1, counters[i].key, counters[i].value);
    }
    
    return 0;
}