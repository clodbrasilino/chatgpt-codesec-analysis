#include <stdio.h>

#define MAX_SIZE 100

void get_frequency(int arr[], int freq[], int size) {
    int i, j, count;

    for(i=0; i<size; i++){
        count = 1;
        for(j=i+1; j<size; j++){
            if(arr[i] == arr[j]){
                count++;
                freq[j] = 0;
            }
        }

        if(freq[i] != 0){
            freq[i] = count;
        }
    }
}

int main() {
    int arr[MAX_SIZE], freq[MAX_SIZE];
    int size, i;

    printf("Enter size of the array : ");
    scanf("%d", &size);

    printf("Enter elements in array : ");
    for(i=0; i<size; i++){
        scanf("%d", &arr[i]);
        freq[i] = -1;
    }

    get_frequency(arr, freq, size);

    for(i=0; i<size; i++){
        if(freq[i] != 0){
            printf("%d occurs %d times\n", arr[i], freq[i]);
        }
    }

    return 0;
}