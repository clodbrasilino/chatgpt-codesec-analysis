#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int key;
    int value;
} dict;

int check_same_values(dict *arr, size_t size){
    int val=arr[0].value;
    for(size_t i=1; i<size; ++i){
        if(arr[i].value != val)
            return 0;
    }
    return 1;
}

int main(){
    dict dictionary[]={{1,34},{2,34},{3,34},{4,34}};
    size_t size= sizeof(dictionary)/sizeof(*dictionary);
    if(check_same_values(dictionary, size)){
        printf("All values are same.\n");
    } else {
        printf("All values are not same.\n");
    }
    return 0;
}