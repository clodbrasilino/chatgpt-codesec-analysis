#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int *arr;
    int length;
} List;

List* zip_lists(List *list1, List *list2, int n) {
    List *result = malloc(sizeof(List));
    if(!result) {
        return NULL;
    }

    result->arr = malloc(n * sizeof(int));
    if(!result->arr) {
        free(result);
        return NULL;
    }

    for(int i = 0; i < n; i++){
        result->arr[i] = list1->arr[i];
        /* Possible weaknesses found:
         *  heap-based buffer under-read [CWE-127] [-Wanalyzer-out-of-bounds]
         *  use of uninitialized value '*_14 + _17' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        result->arr[++i] = list2->arr[i - 1];
    }
    
    result->length = n;

    return result;
}

int main(){
    int n = 3;
    List list1;
    list1.length = n;
    list1.arr = malloc(n * sizeof(int));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list1.arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list1.arr[0] = 1;
    list1.arr[1] = 3;
    list1.arr[2] = 5;

    List list2;
    list2.length = n;
    list2.arr = malloc(n * sizeof(int));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list2.arr' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list2.arr[0] = 2;
    list2.arr[1] = 4;
    list2.arr[2] = 6;

    List *result = zip_lists(&list1, &list2, n*2);

    if(result){
        printf("Zipped array: ");
        for(int i = 0; i < result->length; i++){
            printf("%d ", result->arr[i]);
        }

        free(result->arr);
        free(result);
    }
    else{
        printf("Failed to allocate memory");
    }

    free(list1.arr);
    free(list2.arr);

    return 0;
}