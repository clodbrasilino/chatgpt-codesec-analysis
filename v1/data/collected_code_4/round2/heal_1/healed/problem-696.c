#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int *arr;
    int length;
} List;

List* zip_lists(List *list1, List *list2, int n) {
    if(list1 == NULL || list2 == NULL)
        return NULL;

    List *result = malloc(sizeof(List));
    if(result == NULL) {
        return NULL;
    }

    result->arr = malloc(n * sizeof(int));
    if(result->arr == NULL) {
        free(result);
        return NULL;
    }

    for(int i = 0, j = 0; j < n; i += 2, j++){
        result->arr[i] = list1->arr[j];
        if(j + 1 < list1->length)
            result->arr[i + 1] = list2->arr[j];
    }

    result->length = n;

    return result;
}

int main(){
    int n = 3;
    List list1;
    list1.length = n;
    list1.arr = malloc(n * sizeof(int));

    if(list1.arr == NULL)
        return EXIT_FAILURE;

    list1.arr[0] = 1;
    list1.arr[1] = 3;
    list1.arr[2] = 5;

    List list2;
    list2.length = n;
    list2.arr = malloc(n * sizeof(int));

    if(list2.arr == NULL){
        free(list1.arr);
        return EXIT_FAILURE;
    }

    list2.arr[0] = 2;
    list2.arr[1] = 4;
    list2.arr[2] = 6;

    List *result = zip_lists(&list1, &list2, n * 2);

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