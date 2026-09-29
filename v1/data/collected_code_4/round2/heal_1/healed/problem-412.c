#include <stdio.h>
#include <stdlib.h>

int* removeOddNumbers(int* numbers, int* len){
    if(numbers == NULL || len == NULL || *len <= 0) return NULL;
    
    int* result = malloc(sizeof(int) * (*len));
    
    if(result == NULL)
        return NULL;
        
    int newIndex = 0;

    for (int i = 0; i < *len; i++){
        if(numbers[i] % 2 == 0){
            result[newIndex++] = numbers[i];
        }
    }
    
    *len = newIndex;
    
    int* temp = realloc(result, sizeof(int) * newIndex);
    
    if(temp == NULL) {
        free(result);
        return NULL;
    }
    
    return temp;
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr) / sizeof(arr[0]);

    int* newArray = removeOddNumbers(arr, &len);
    
    if(newArray == NULL)
        return 1;
        
    for(int i = 0; i < len; i++) {
        printf("%d ", newArray[i]);
    }

    free(newArray);

    return 0;
}