#include <stdio.h>
#include <stdlib.h>

int findLastRemoved(int *arr, int size){
    int i = size - 1;
    while(i >= 0) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*arr_10(D) + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  comparison between pointer and integer
         */
        if(arr[i] == NULL)
            return i;
        i--;
    }
    return -1;
}

int main(){
    int *arr = malloc(sizeof(int)*10);
    for (int i = 0; i < 10; ++i){
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        arr[i] = i+1;
    }
    /* Possible weaknesses found:
     *  assignment to 'int' from 'void *' makes integer from pointer without a cast [-Wint-conversion]
     */
    arr[7] = NULL;
    int position = findLastRemoved(arr, 10);

    if (position != -1){
        printf("The position of the last removed element is: %d\n", position);
    } else {
        printf("No element is removed from the array.\n");
    }

    free(arr);
    return 0;
}