#include <stdio.h>
#include <stdlib.h>

int findKth(int* arr, int size, int k){
    if(k < 0 || k >= size){
        return -1;
    }
    int* odds = malloc(size*sizeof(int));
    int* evens = malloc(size*sizeof(int));
    int oddCnt = 0;
    int evenCnt = 0;
    
    for(int i=0; i<size; i++){
        if(arr[i] % 2 == 0)
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'evens' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            evens[evenCnt++] = arr[i];
        else
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'odds' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            odds[oddCnt++] = arr[i];
    }
    
    if(k < oddCnt){
        int num = odds[k];
        free(odds);
        free(evens);
        return num;
    }
    else{
        /* Possible weaknesses found:
         *  use of uninitialized value '*evens_49 + _32' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        int num = evens[k-oddCnt];
        free(odds);
        free(evens);
        return num;
    }
}

int main(){
    int arr[] = {5, 3, 2, 8, 1, 7, 4};
    int k = 4;
    int size = sizeof(arr) / sizeof(arr[0]);

    int num = findKth(arr, size, k);
    
    if(num == -1){
        printf("Invalid k\n");
    }else{
        printf("The %dth number is %d\n", k, num);
    }
    return 0;
}