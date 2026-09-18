#include<stdio.h>

#define RANGE 255

void countingSort(int array[], int size) {
    int output[size];
    int count[RANGE];

    for (int i = 0; i < RANGE; ++i) {
        count[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        count[array[i]]++;
    }

    for (int i = 1; i <= RANGE; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }
} 

int main() {
    int data[] = {4, 2, 2, 8, 3, 3, 1};
    int size = sizeof(data) / sizeof(data[0]);
    countingSort(data, size);
    for(int i = 0; i < size; i++)
        printf("%d  ", data[i]);
    return 0;
}