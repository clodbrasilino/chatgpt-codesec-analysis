#include <stdio.h>
#define MAX_SIZE 100

void getFrequency(int arr[], int size) {
    int count[MAX_SIZE] = {0};

    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
    }

    printf("Frequency of elements in the array:\n");
    for (int i = 0; i < size; i++) {
        // checks the frequency count and print only when count is nonzero
        if (count[arr[i]] != 0) {
            printf("%d: %d\n", arr[i], count[arr[i]]);
            count[arr[i]] = 0;
        }
    }
}

int main() {
    int size=0;

    printf("Enter the size of the list: ");
    scanf("%d", &size);
    
    // if user enters size larger than predefined max size, it will limit the size to max size
    if(size>MAX_SIZE){
        size = MAX_SIZE;
    }

    int arr[MAX_SIZE] = {0};
    printf("Enter the elements of the list: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    getFrequency(arr, size);

    return 0;
}