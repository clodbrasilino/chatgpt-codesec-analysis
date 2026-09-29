#include <stdio.h>
#define MAX_SIZE 100

void findFrequency(int arr[], int size) {
    int freq[MAX_SIZE], visited = -1;

    for(int i = 0; i < size; i++) {
        int count = 1;
        for(int j = i + 1; j < size; j++) {
            if(arr[i] == arr[j]) {
                count++;
                freq[j] = visited;
            }
        }
        if(freq[i] != visited)
            freq[i] = count;
    }

    for(int i = 0; i < size; i++) {
        if(freq[i] != visited) {
            printf("%d occurs %d times\n", arr[i], freq[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 8, 3, 2, 2, 2, 5, 1};
    int size = sizeof(arr)/sizeof(int);

    findFrequency(arr, size);

    return 0;
}