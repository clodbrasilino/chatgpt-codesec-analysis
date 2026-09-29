#include <stdio.h>
#include <stdlib.h>

void splitArray(int *arr, int length, int position) {
    int *temp = (int *)malloc(length * sizeof(int));
    
    if(temp == NULL) {
        printf("Couldn't allocate memory.");
        return;
    }

    for (int i = 0; i < length; i++) {
        temp[(i + length - position) % length] = arr[i];
    }

    for (int i = 0; i < length; i++) {
        arr[i] = temp[i];
    }

    free(temp);
}


int main () {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    int pos = 3;

    splitArray(arr, len, pos);

    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}