#include <stdio.h>
#include <stdlib.h>

int* removeOddNumbers(int* numbers, int* len){
    int* result = malloc(sizeof(int) * (*len));
    int newIndex = 0;

    for (int i = 0; i < *len; i++){
        if(numbers[i] % 2 == 0){
            result[newIndex++] = numbers[i];
        }
    }

    *len = newIndex;
    return realloc(result, sizeof(int) * newIndex);
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr) / sizeof(arr[0]);

    int* newArray = removeOddNumbers(arr, &len);

    for(int i = 0; i < len; i++) {
        printf("%d ", newArray[i]);
    }

    free(newArray);
    return 0;
}