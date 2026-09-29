#include <stdio.h>
#include <stdlib.h>

int* removeOddNumbers(int* numbers, int* len){
    int* result = malloc(sizeof(int) * (*len));
    int newIndex = 0;

    for (int i = 0; i < *len; i++){
        if(numbers[i] % 2 == 0){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[newIndex++] = numbers[i];
        }
    }

    *len = newIndex;
    /* Possible weaknesses found:
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return realloc(result, sizeof(int) * newIndex);
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(arr) / sizeof(arr[0]);

    int* newArray = removeOddNumbers(arr, &len);

    for(int i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  dereference of NULL 'newArray' [CWE-476] [-Wanalyzer-null-dereference]
         */
        printf("%d ", newArray[i]);
    }

    free(newArray);
    return 0;
}