#include <stdio.h>

int find_frequency(int *arr, int size, int num) {
    int frequency = 0;
    if(arr != NULL && size > 0) {
        for(int i = 0; i < size; i++) {
            if(arr[i] == num) {
                frequency++;
            }
        }
    }
    return frequency;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 3, 2, 1};
    int size = sizeof(arr)/sizeof(arr[0]);
    int num = 2;

    int freq = find_frequency(arr, size, num);
    printf("Frequency of %d is %d", num, freq);

    return 0;
}